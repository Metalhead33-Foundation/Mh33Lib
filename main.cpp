#include <iostream>
#include <IoSys/MhFilesystem.hpp>
#include <IoSys/PhysFSIoSystem.hpp>

int main(int argc, char *argv[])
{
	PhysFS::IoSystem::initialize(argv[0]);
	PhysFS::IoSystem fs;
	fs.mount("/home/legacy/zene/GameMusic/Unreal Tournament/","/",false);
	fs.enumerate("/mod",false,[](const char* path) {
		std::cout << path << std::endl;
	} );
	PhysFS::IoSystem::deinitialize();
	return 0;
}

