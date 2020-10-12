#ifndef MHBUFFERWRAPPER_HPP
#define MHBUFFERWRAPPER_HPP
#include "MhIoDevice.hpp"
#include "MhBuffer.hpp"

namespace MH33 {

class BufferWrapper : public IoDevice
{
private:
	Buffer buffer;
	intptr_t cursor;
public:
	// Copy and move constructors and assignments - from other wrappers
	BufferWrapper(const BufferWrapper& cpy);
	BufferWrapper(BufferWrapper&& mov);
	BufferWrapper& operator=(const BufferWrapper& cpy);
	BufferWrapper& operator=(BufferWrapper&& mov);
	// Copy and move constructors - from other buffers
	BufferWrapper(const Buffer& cpy);
	BufferWrapper(Buffer&& mov);
	// Default constructor
	BufferWrapper();
	BufferWrapper(size_t sz);
	// Direct buffer access, in case we need it.
	Buffer& getBuffer();
	const Buffer& getBuffer() const;
	// Actual IO functions
	bool flush();
	bool seek(SeekOrigin whence, intptr_t offset);
	intptr_t tell();
	intptr_t size();
	size_t write(const void* data, size_t dataSize);
	size_t read(void* destination, size_t dataSize);
	IoMode getMode() const;
	void yield(Buffer& target);
};

}
#endif // MHBUFFERWRAPPER_HPP
