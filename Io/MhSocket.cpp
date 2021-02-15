#include <Io/MhSocket.hpp>
#if defined(_WIN32)
#include "private/MhSockeWin32.hpp"
#elif defined(__unix__)
#include "private/MhSocketUnix.hpp"
#endif

namespace MH33 {
namespace Io {
Socket::Socket() : impl(nullptr)
{

}

bool Socket::flush()
{

}

bool Socket::seek(SeekOrigin whence, intptr_t offset)
{
	return false;
}

intptr_t Socket::tell()
{
	return -1; // Sequential.
}

intptr_t Socket::size()
{
	return -1; // Sequential
}

size_t Socket::write(const void *data, size_t dataSize)
{
	return impl->sendMessage(data,dataSize);
}

size_t Socket::read(void *destination, size_t dataSize)
{
	return impl->receiveMessage(destination,dataSize);
}

Mode Socket::getMode() const
{
	return mode;
}

bool Socket::isValid() const
{
	return impl != nullptr;
}
}
}
