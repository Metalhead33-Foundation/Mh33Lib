#ifndef MHIODEVICE_HPP
#define MHIODEVICE_HPP
#include <cstddef>
#include <cstdint>
#include <functional>
#include "MhBuffer.hpp"
namespace MH33 {

enum class SeekOrigin {
	SET, // Beginning of file
	CUR, // Current position
	END // End of file
};

enum class IoMode {
	READ = 1,
	WRITE = 2,
	APPEND = 4,
	READ_WRITE = (READ | WRITE),
	READ_APPEND = (READ | APPEND)
};

class IoDevice {
public:
	virtual ~IoDevice() = default;
	virtual bool flush() = 0;
	virtual bool seek(SeekOrigin whence, intptr_t offset) = 0;
	virtual intptr_t tell() = 0;
	virtual intptr_t size() = 0;
	virtual size_t write(const void* data, size_t dataSize) = 0;
	virtual size_t read(void* destination, size_t dataSize) = 0;
	virtual IoMode getMode() const = 0;
	// A convenience function
	void readAll(Buffer& dst) {
		auto sz = size()-tell();
		dst.resize(sz);
		read(dst.data(),sz);
	}
	Buffer readAll(void) {
		Buffer tmp;
		readAll(tmp);
		return tmp;
	}
	size_t write(const Buffer& src) {
		return write(src.data(),src.size());
	}
};
typedef std::function<IoDevice*(IoMode)> IoDeviceCreator;

}
#endif // MHIODEVICE_HPP
