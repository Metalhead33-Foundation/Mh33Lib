#include "PhysFSIoSystem.hpp"
#include  <Io/PhysFSIO.hpp>
#include <physfs.h>

namespace PhysFS {

IoSystem::IoSystem()
{

}

MH33::Io::Device *IoSystem::open(const char *path, MH33::Io::Mode mode)
{
	return new IO(path,mode);
}

bool IoSystem::exists(const char *path)
{
	return PHYSFS_exists(path);
}

char IoSystem::separator() const
{
	return PHYSFS_getDirSeparator()[0];
}

void IoSystem::enumerate(const char *path, std::vector<std::string> &output)
{
	char **rc = PHYSFS_enumerateFiles(path);
	char **i;
	for (i = rc; *i != nullptr; i++) {
		output.emplace_back(*i);
	}
	PHYSFS_freeList(rc);
}

void IoSystem::enumerate(const char *path, IoSystem::FilenameCallback functor)
{
	char **rc = PHYSFS_enumerateFiles(path);
	char **i;
	for (i = rc; *i != nullptr; i++) {
		functor(*i);
	}
	PHYSFS_freeList(rc);
}

}
