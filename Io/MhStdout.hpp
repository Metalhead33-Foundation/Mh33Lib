#ifndef MHSTDOUT_HPP
#define MHSTDOUT_HPP
#include "MhIoDevice.hpp"
#include <cstdio>

namespace MH33 {

class Stdout : public IoDevice
{
public:
	Stdout();
	bool flush();
	bool seek(SeekOrigin whence, intptr_t offset);
	intptr_t tell();
	intptr_t size();
	size_t write(const void* data, size_t dataSize);
	size_t read(void* destination, size_t dataSize);
	IoMode getMode() const;
};

}
#endif // MHSTDOUT_HPP
