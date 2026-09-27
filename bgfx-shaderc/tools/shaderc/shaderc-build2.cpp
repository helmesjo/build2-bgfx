// Handle --build2-metadata in main() (see also buildfile).

#define main xmain
#include "shaderc.cpp"
#undef main

#include <stdio.h>
#include <string.h>

int main(int _argc, const char* _argv[])
{
	if (_argc == 2 && strncmp(_argv[1], "--build2-metadata=", 18) == 0)
	{
		printf("# build2 buildfile shaderc\n"
		       "export.metadata = 1 shaderc\n"
		       "shaderc.name = [string] shaderc\n"
		       "shaderc.version = [string] " SHADERC_BUILD2_VERSION "\n"
		       "shaderc.checksum = [string] " SHADERC_BUILD2_VERSION "\n");
		return 0;
	}

	return xmain(_argc, _argv);
}
