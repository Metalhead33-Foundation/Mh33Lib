#ifndef MHSOCKET_HPP
#define MHSOCKET_HPP
#include "MhIoDevice.hpp"
#include <memory>

namespace MH33 {

enum class CONNECTION_TYPE {
	DISCONNECTED,
	CONNECTED,
	BOUND
};

union ReceptClass {
	timeval tim;
	int integer;
	uint64_t pad64;
};

class Socket : public IoDevice
{
private:
	struct SocketPriv;
	std::unique_ptr<SocketPriv> impl;
	MH33::IoMode mode;
public:
	Socket();
	// Socket functions
	bool flush();
	bool seek(MH33::SeekOrigin whence, intptr_t offset);
	intptr_t tell();
	intptr_t size();
	size_t write(const void* data, size_t dataSize);
	size_t read(void* destination, size_t dataSize);
	MH33::IoMode getMode() const;
};
}

#endif // MHSOCKET_HPP
