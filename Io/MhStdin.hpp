#ifndef MHSTDIN_HPP
#define MHSTDIN_HPP
#include "MhIoDevice.hpp"
#include <cstdio>

namespace MH33 {

class Stdin : public IoDevice
{
public:
	Stdin();
	bool flush();
	bool seek(SeekOrigin whence, intptr_t offset);
	intptr_t tell();
	intptr_t size();
	size_t write(const void* data, size_t dataSize);
	size_t read(void* destination, size_t dataSize);
	IoMode getMode() const;
};

}
#endif // MHSTDIN_HPP
