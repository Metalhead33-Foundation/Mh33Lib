#ifndef MHSTDERR_HPP
#define MHSTDERR_HPP
#include "MhIoDevice.hpp"
#include <cstdio>

namespace MH33 {

class Stderr : public IoDevice
{
public:
	Stderr();
	bool flush();
	bool seek(SeekOrigin whence, intptr_t offset);
	intptr_t tell();
	intptr_t size();
	size_t write(const void* data, size_t dataSize);
	size_t read(void* destination, size_t dataSize);
	IoMode getMode() const;
};

}
#endif // MHSTDERR_HPP
