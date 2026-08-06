/*
 * Shader bin loader for examples that only need loadProgram() (e.g. 01-cubes).
 * Subset of upstream examples/common/bgfx_utils.cpp loadShader/loadProgram path.
 * Prefer full bgfx_utils when decode/mesh support is packaged.
 */

#include "common.h"

#include <bgfx/bgfx.h>
#include <bx/readerwriter.h>
#include <bx/string.h>
#include "entry/entry.h"
#include "entry/dbg.h"
#include "bgfx_utils.h"

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
