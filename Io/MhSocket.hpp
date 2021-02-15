#ifndef MHSOCKET_HPP
#define MHSOCKET_HPP
#include <Io/MhIoDevice.hpp>
#include <memory>

namespace MH33 {
namespace Io {

enum class CONNECTION_TYPE {
	DISCONNECTED,
	CONNECTED,
	BOUND
};

union ReceiptClass {
	timeval tim;
	int integer;
	uint64_t pad64;
};

class Socket : public Device
{
private:
	struct SocketPriv;
	std::unique_ptr<SocketPriv> impl;
	MH33::Io::Mode mode;
public:
	Socket();
	~Socket() = default;
	// Socket functions
	bool flush();
	bool seek(MH33::Io::SeekOrigin whence, intptr_t offset);
	intptr_t tell();
	intptr_t size();
	size_t write(const void* data, size_t dataSize);
	size_t read(void* destination, size_t dataSize);
	MH33::Io::Mode getMode() const;
	bool isValid() const;
};

}
}

#endif // MHSOCKET_HPP
