/*
 * Shader bin loader for examples that only need loadProgram() (e.g. 01-cubes).
 * Subset of upstream examples/common/bgfx_utils.cpp loadShader/loadProgram path.
 * Prefer full bgfx_utils when decode/mesh support is packaged.
 */

#include "common.h"

#include <bgfx/bgfx.h>
#include <bimg/decode.h>
#include <bx/allocator.h>
#include <bx/error.h>
#include <bx/math.h>
#include <bx/readerwriter.h>
#include <bx/string.h>
#include "entry/entry.h"
#include "entry/dbg.h"
#include "bgfx_utils.h"

static bx::FilePath resolveRuntimePath(const bx::FilePath& _filePath)
{
#ifdef BGFX_EXAMPLES_RUNTIME_DIR
	bx::FilePath filePath(BGFX_EXAMPLES_RUNTIME_DIR);
	filePath.join(_filePath.getCPtr() );
	return filePath;
#else
	return _filePath;
#endif
}

static const bgfx::Memory* loadMem(bx::FileReaderI* _reader, const bx::FilePath& _filePath)
{
	if (bx::open(_reader, _filePath) )
	{
		uint32_t size = (uint32_t)bx::getSize(_reader);
		const bgfx::Memory* mem = bgfx::alloc(size+1);
		bx::read(_reader, mem->data, size, bx::ErrorAssert{});
		bx::close(_reader);
		mem->data[mem->size-1] = '\0';
		return mem;
	}

	DBG("Failed to load %s.", _filePath.getCPtr() );
	return NULL;
}

static bgfx::ShaderHandle loadShader(bx::FileReaderI* _reader, const bx::StringView& _name)
{
	// Prefer package-absolute path so CWD does not matter. Fallback matches
	// upstream (run from the directory that contains shaders/).
	//
#ifndef BGFX_EXAMPLES_SHADERS_DIR
#	define BGFX_EXAMPLES_SHADERS_DIR "shaders"
#endif
	bx::FilePath filePath(BGFX_EXAMPLES_SHADERS_DIR);

	switch (bgfx::getRendererType() )
	{

	case bgfx::RendererType::Noop:
	case bgfx::RendererType::Direct3D11: filePath.join("dxbc");  break;
	case bgfx::RendererType::Direct3D12: filePath.join("dxil");  break;
	case bgfx::RendererType::Agc:
	case bgfx::RendererType::Gnm:        filePath.join("pssl");  break;
	case bgfx::RendererType::Metal:      filePath.join("metal"); break;
	case bgfx::RendererType::Nvn:        filePath.join("nvn");   break;
	case bgfx::RendererType::OpenGL:     filePath.join("glsl");  break;
	case bgfx::RendererType::OpenGLES:   filePath.join("essl");  break;
	case bgfx::RendererType::Vulkan:     filePath.join("spirv"); break;
	case bgfx::RendererType::WebGPU:     filePath.join("wgsl");  break;

	case bgfx::RendererType::Count:
		BX_ASSERT(false, "You should not be here!");
		break;
	}

	char fileName[512];
	bx::strCopy(fileName, BX_COUNTOF(fileName), _name);
	bx::strCat(fileName, BX_COUNTOF(fileName), ".bin");

	filePath.join(fileName);

	bgfx::ShaderHandle handle = bgfx::createShader(loadMem(_reader, filePath.getCPtr() ) );
	bgfx::setName(handle, _name.getPtr(), _name.getLength() );

	return handle;
}

bgfx::ShaderHandle loadShader(const bx::StringView& _name)
{
	return loadShader(entry::getFileReader(), _name);
}

bgfx::ProgramHandle loadProgram(const bx::StringView& _vsName, const bx::StringView& _fsName)
{
	bgfx::ShaderHandle vsh = loadShader(entry::getFileReader(), _vsName);
	bgfx::ShaderHandle fsh = BGFX_INVALID_HANDLE;
	if (!_fsName.isEmpty() )
	{
		fsh = loadShader(entry::getFileReader(), _fsName);
	}

	return bgfx::createProgram(vsh, fsh, true /* destroy shaders when program is destroyed */);
}

void* load(const bx::FilePath& _filePath, uint32_t* _size)
{
	bx::FilePath filePath = resolveRuntimePath(_filePath);
	bx::FileReaderI* reader = entry::getFileReader();
	bx::AllocatorI* allocator = entry::getAllocator();

	if (bx::open(reader, filePath) )
	{
		uint32_t size = (uint32_t)bx::getSize(reader);
		void* data = bx::alloc(allocator, size);
		bx::read(reader, data, size, bx::ErrorAssert{});
		bx::close(reader);
		if (NULL != _size)
		{
			*_size = size;
		}
		return data;
	}

	DBG("Failed to open: %s.", filePath.getCPtr() );

	if (NULL != _size)
	{
		*_size = 0;
	}

	return NULL;
}

void unload(void* _ptr)
{
	bx::free(entry::getAllocator(), _ptr);
}

static void imageReleaseCb(void* _ptr, void* _userData)
{
	BX_UNUSED(_ptr);
	bimg::ImageContainer* imageContainer = (bimg::ImageContainer*)_userData;
	bimg::imageFree(imageContainer);
}

bgfx::TextureHandle loadTexture(const bx::FilePath& _filePath, uint64_t _flags, uint8_t _skip, bgfx::TextureInfo* _info, bimg::Orientation::Enum* _orientation, bx::Error* _err)
{
	BX_UNUSED(_skip);
	bgfx::TextureHandle handle = BGFX_INVALID_HANDLE;

	if (NULL != _info)
	{
		bx::memSet(_info, 0, sizeof(*_info) );
		_info->format = bgfx::TextureFormat::Unknown;
	}

	if (NULL != _orientation)
	{
		*_orientation = bimg::Orientation::R0;
	}

	uint32_t size;
	void* data = load(_filePath, &size);
	if (NULL != data)
	{
		bx::Error localErr;
		bx::Error* err = (NULL != _err) ? _err : &localErr;
		bimg::ImageContainer* imageContainer = bimg::imageParse(entry::getAllocator(), data, size, bimg::TextureFormat::Count, err);

		if (NULL != imageContainer)
		{
			if (NULL != _orientation)
			{
				*_orientation = imageContainer->m_orientation;
			}

			const bgfx::Memory* mem = bgfx::makeRef(
				  imageContainer->m_data
				, imageContainer->m_size
				, imageReleaseCb
				, imageContainer
				);
			unload(data);

			if (NULL != _info)
			{
				bgfx::calcTextureSize(
					  *_info
					, uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, uint16_t(imageContainer->m_depth)
					, imageContainer->m_cubeMap
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					);
			}

			if (imageContainer->m_cubeMap)
			{
				handle = bgfx::createTextureCube(
					  uint16_t(imageContainer->m_width)
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, mem
					);
			}
			else if (1 < imageContainer->m_depth)
			{
				handle = bgfx::createTexture3D(
					  uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, uint16_t(imageContainer->m_depth)
					, 1 < imageContainer->m_numMips
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, mem
					);
			}
			else if (bgfx::isTextureValid(0, false, imageContainer->m_numLayers, bgfx::TextureFormat::Enum(imageContainer->m_format), _flags) )
			{
				handle = bgfx::createTexture2D(
					  uint16_t(imageContainer->m_width)
					, uint16_t(imageContainer->m_height)
					, 1 < imageContainer->m_numMips
					, imageContainer->m_numLayers
					, bgfx::TextureFormat::Enum(imageContainer->m_format)
					, _flags
					, mem
					);
			}

			if (bgfx::isValid(handle) )
			{
				const bx::StringView name(_filePath);
				bgfx::setName(handle, name.getPtr(), name.getLength() );
			}
		}
	}

	return handle;
}

bimg::ImageContainer* imageLoad(const bx::FilePath& _filePath, bgfx::TextureFormat::Enum _dstFormat)
{
	uint32_t size = 0;
	void* data = load(_filePath, &size);
	if (NULL == data)
	{
		return NULL;
	}

	return bimg::imageParse(entry::getAllocator(), data, size, bimg::TextureFormat::Enum(_dstFormat) );
}

void calcTangents(void* _vertices, uint16_t _numVertices, bgfx::VertexLayout _layout, const uint16_t* _indices, uint32_t _numIndices)
{
	struct PosTexcoord
	{
		float m_x;
		float m_y;
		float m_z;
		float m_pad0;
		float m_u;
		float m_v;
		float m_pad1;
		float m_pad2;
	};

	float* tangents = new float[6*_numVertices];
	bx::memSet(tangents, 0, 6*_numVertices*sizeof(float) );

	PosTexcoord v0;
	PosTexcoord v1;
	PosTexcoord v2;

	for (uint32_t ii = 0, num = _numIndices/3; ii < num; ++ii)
	{
		const uint16_t* indices = &_indices[ii*3];
		uint32_t i0 = indices[0];
		uint32_t i1 = indices[1];
		uint32_t i2 = indices[2];

		bgfx::vertexUnpack(&v0.m_x, bgfx::Attrib::Position, _layout, _vertices, i0);
		bgfx::vertexUnpack(&v0.m_u, bgfx::Attrib::TexCoord0, _layout, _vertices, i0);

		bgfx::vertexUnpack(&v1.m_x, bgfx::Attrib::Position, _layout, _vertices, i1);
		bgfx::vertexUnpack(&v1.m_u, bgfx::Attrib::TexCoord0, _layout, _vertices, i1);

		bgfx::vertexUnpack(&v2.m_x, bgfx::Attrib::Position, _layout, _vertices, i2);
		bgfx::vertexUnpack(&v2.m_u, bgfx::Attrib::TexCoord0, _layout, _vertices, i2);

		const float bax = v1.m_x - v0.m_x;
		const float bay = v1.m_y - v0.m_y;
		const float baz = v1.m_z - v0.m_z;
		const float bau = v1.m_u - v0.m_u;
		const float bav = v1.m_v - v0.m_v;

		const float cax = v2.m_x - v0.m_x;
		const float cay = v2.m_y - v0.m_y;
		const float caz = v2.m_z - v0.m_z;
		const float cau = v2.m_u - v0.m_u;
		const float cav = v2.m_v - v0.m_v;

		const float det = (bau * cav - bav * cau);
		const float invDet = 1.0f / det;

		const float tx = (bax * cav - cax * bav) * invDet;
		const float ty = (bay * cav - cay * bav) * invDet;
		const float tz = (baz * cav - caz * bav) * invDet;

		const float bx = (cax * bau - bax * cau) * invDet;
		const float by = (cay * bau - bay * cau) * invDet;
		const float bz = (caz * bau - baz * cau) * invDet;

		for (uint32_t jj = 0; jj < 3; ++jj)
		{
			float* tanu = &tangents[indices[jj]*6];
			float* tanv = &tanu[3];
			tanu[0] += tx;
			tanu[1] += ty;
			tanu[2] += tz;

			tanv[0] += bx;
			tanv[1] += by;
			tanv[2] += bz;
		}
	}

	for (uint32_t ii = 0; ii < _numVertices; ++ii)
	{
		const bx::Vec3 tanu = bx::load<bx::Vec3>(&tangents[ii*6]);
		const bx::Vec3 tanv = bx::load<bx::Vec3>(&tangents[ii*6 + 3]);

		float nxyzw[4];
		bgfx::vertexUnpack(nxyzw, bgfx::Attrib::Normal, _layout, _vertices, ii);

		const bx::Vec3 normal  = bx::load<bx::Vec3>(nxyzw);
		const float    ndt     = bx::dot(normal, tanu);
		const bx::Vec3 nxt     = bx::cross(normal, tanu);
		const bx::Vec3 tmp     = bx::sub(tanu, bx::mul(normal, ndt) );

		float tangent[4];
		bx::store(tangent, bx::normalize(tmp) );
		tangent[3] = bx::dot(nxt, tanv) < 0.0f ? -1.0f : 1.0f;

		bgfx::vertexPack(tangent, true, bgfx::Attrib::Tangent, _layout, _vertices, ii);
	}

	delete [] tangents;
}
