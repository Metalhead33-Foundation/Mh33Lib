#include "MhFilesystem.hpp"
#include <Io/MhFile.hpp>
#include <filesystem>

namespace MH33 {
namespace Io {

Filesystem::Filesystem()
{

}

Device *Filesystem::open(const char *path, Mode mode)
{
	return new File(path,mode);
}

bool Filesystem::exists(const char *path)
{
	return std::filesystem::exists(path);
}

char Filesystem::separator() const
{
#if defined(_WIN32)
	return '\\';
#elif defined(__unix)
	return '/';
#else
#error "Unknown operating system, we don't know what the OS separator is!"
#endif
}

void Filesystem::enumerate(const char *path, bool withPath, std::vector<std::string> &output)
{
	auto tmpath = std::filesystem::directory_iterator(path);
	if(withPath) {
		for(const auto& p : tmpath ) {
			output.push_back(p.path().string());
		}
	} else {
	for(const auto& p : tmpath ) {
		output.push_back(p.path().filename().string());
	}
	}
}

void Filesystem::enumerate(const char *path, bool withPath, System::FilenameCallback functor)
{
	auto tmpath = std::filesystem::directory_iterator(path);
	if(withPath) {
		for(const auto& p : tmpath ) {
			functor(p.path().c_str());
		}
	} else {
		for(const auto& p : tmpath ) {
			functor(p.path().filename().c_str());
		}
	}
}

bool Filesystem::isDirectory(const char *path)
{
	return std::filesystem::is_directory(path);
}

bool Filesystem::isSymlink(const char *path)
{
	return std::filesystem::is_symlink(path);
}

bool Filesystem::isFile(const char *path)
{
	return std::filesystem::is_fifo(path);
}

bool Filesystem::mkdir(const char *dir)
{
	return std::filesystem::create_directory(dir);
}

}
}
