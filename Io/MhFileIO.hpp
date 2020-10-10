#ifndef MHFILEIO_HPP
#define MHFILEIO_HPP
#include "MhIoDevice.hpp"
#include <cstdio>
#include <string>

namespace MH33 {

class FileIO : public IoDevice
{
private:
	FILE* fdev;
	IoMode mode;
	FileIO(const FileIO& cpy) = delete; // No copy constructor
	FileIO& operator=(const FileIO& cpy) = delete; // No copy assignment operator
public:
	// Destructor
	~FileIO();
	// Move constructor
	FileIO(FileIO&& mov);
	// Move assignment operator
	FileIO& operator=(FileIO&& mov);
	// Default constructor
	FileIO();
	// Actual constructor
	FileIO(const char* path, IoMode mode);
	FileIO(const std::string& path, IoMode mode);
	// Actual imnplementation
	bool flush();
	bool seek(SeekOrigin whence, intptr_t offset);
	intptr_t tell();
	intptr_t size();
	size_t write(const void* data, size_t dataSize);
	size_t read(void* destination, size_t dataSize);
	IoMode getMode() const;
	// Convenience function
	size_t readAll(Buffer& dst) {
		auto sz = size();
		dst.resize(sz);
		return read(dst.data(),sz);
	}
};

}
#endif // MHFILEIO_HPP
