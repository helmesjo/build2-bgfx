// Handle --build2-metadata in main() (see also buildfile).

#define main xmain
#include "geometryc.cpp"
#undef main

#include <stdio.h>
#include <string.h>

int main(int _argc, const char* _argv[])
{
	if (_argc == 2 && strncmp(_argv[1], "--build2-metadata=", 18) == 0)
	{
		printf("# build2 buildfile geometryc\n"
		       "export.metadata = 1 geometryc\n"
		       "geometryc.name = [string] geometryc\n"
		       "geometryc.version = [string] " GEOMETRYC_BUILD2_VERSION "\n"
		       "geometryc.checksum = [string] " GEOMETRYC_BUILD2_VERSION "\n");
		return 0;
	}

	return xmain(_argc, _argv);
}
