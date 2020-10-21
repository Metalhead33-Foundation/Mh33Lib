#include <iostream>
#include <IoSys/MhFilesystem.hpp>
#include <IoSys/PhysFSIoSystem.hpp>

int main(int argc, char *argv[])
{
	MH33::Io::Filesystem fs;
	fs.enumerate("/home/legacy/zene/middleages/music",[](MH33::Io::System* sys, const char* path, const char* fname) {
		std::cout << "System: [" << reinterpret_cast<void*>(sys) << "]\n";
		std::cout << "Full Path: " << path << "\n";
		std::cout << "Filename: " << fname;
		std::cout << std::endl;
	} );
	return 0;
}

