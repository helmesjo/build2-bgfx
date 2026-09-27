// Handle --build2-metadata in main() (see also buildfile).

#define main xmain
#include "texturec.cpp"
#undef main

#include <stdio.h>
#include <string.h>

int main(int _argc, const char* _argv[])
{
	if (_argc == 2 && strncmp(_argv[1], "--build2-metadata=", 18) == 0)
	{
		printf("# build2 buildfile texturec\n"
		       "export.metadata = 1 texturec\n"
		       "texturec.name = [string] texturec\n"
		       "texturec.version = [string] " TEXTUREC_BUILD2_VERSION "\n"
		       "texturec.checksum = [string] " TEXTUREC_BUILD2_VERSION "\n");
		return 0;
	}

	return xmain(_argc, _argv);
}
