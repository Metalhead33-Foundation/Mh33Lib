#ifndef PHYSFSIOSYSTEM_HPP
#define PHYSFSIOSYSTEM_HPP
#include "MhIoSystem.hpp"
namespace PhysFS {

class IoSystem : public MH33::Io::System
{
public:
	IoSystem();

	MH33::Io::Device* open(const char* path, MH33::Io::Mode mode);
	bool exists(const char* path);
	char separator() const;
	void enumerate(const char* path, std::vector<std::string>& output);
	void enumerate(const char* path, FilenameCallback functor);
};

}
#endif // PHYSFSIOSYSTEM_HPP
