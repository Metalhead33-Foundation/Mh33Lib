#ifndef PHYSFSIO_HPP
#define PHYSFSIO_HPP
#include "MhIoDevice.hpp"
#include <string>
namespace PhysFS {

class IO
{
	void* handle;
	MH33::IoMode mode;
	IO(const IO& cpy) = delete; // No copy constructor
	IO& operator=(const IO& cpy) = delete; // No copy assignment operator
public:
	// Destructor
	~IO();
	// Move constructor
	IO(IO&& mov);
	// Move assignment operator
	IO& operator=(IO&& mov);
	// Default constructor
	IO();
	// Actual constructor
	IO(const char* path, MH33::IoMode mode);
	IO(const std::string& path, MH33::IoMode mode);
	// Actual imnplementation
	bool flush();
	bool seek(MH33::SeekOrigin whence, intptr_t offset);
	intptr_t tell();
	intptr_t size();
	size_t write(const void* data, size_t dataSize);
	size_t read(void* destination, size_t dataSize);
	MH33::IoMode getMode() const;
};

}

#endif // PHYSFSIO_HPP
