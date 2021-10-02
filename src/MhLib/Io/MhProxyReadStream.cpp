#include <MhLib/Io/MhProxyReadStream.hpp>
#include <cstring>

namespace MH33 {
namespace Io {

ProxyReadStream::ProxyReadStream(size_t inBuffSize, size_t outBuffSize) : inFront(nullptr), inBuff(inBuffSize), outBuff(outBuffSize),
	inBuffCursor(0), inBuffSize(0), outBuffCursor(0), outBuffEnd(0)
{

}

Device *ProxyReadStream::getInFront() const
{
	return inFront;
}

void ProxyReadStream::setInFront(Device *value)
{
	inFront = value;
}

ProxyReadStream::ProxyReadStream(Device *inFront, size_t inBuffSize, size_t outBuffSize) : inFront(inFront), inBuff(inBuffSize), outBuff(outBuffSize),
	inBuffCursor(0), inBuffSize(0), outBuffCursor(0), outBuffEnd(0)
{

}

bool ProxyReadStream::flush()
{
	return false;
}

bool ProxyReadStream::seek(SeekOrigin whence, intptr_t offset)
{
	(void)whence;
	(void)offset;
	return false;
}

intptr_t ProxyReadStream::tell()
{
	return -1;
}

intptr_t ProxyReadStream::size()
{
	return -1;
}

size_t ProxyReadStream::write(const void *data, size_t dataSize)
{
	(void)data;
	(void)dataSize;
	return 0; // Read-only stream
}

/*
	Device* inFront;
	std::vector<std::byte> inBuff;
	size_t inBuffCursor;
	size_t inBuffEnd;
	std::vector<std::byte> outBuff;
	size_t outBuffCursor;
	size_t outBuffEnd;
*/

size_t ProxyReadStream::read(void *destination, size_t dataSize)
{
	if(inFront) {
		size_t cursor = 0;
		while(cursor < dataSize) {
			// inFront->read(inBuff.data(),inBuff.size())
			if(outBuffCursor < outBuffEnd)
			{
				const size_t dataToCopy = outBuffEnd-outBuffCursor;
				std::memcpy(&reinterpret_cast<std::byte*>(destination)[cursor],&outBuff[outBuffCursor],dataToCopy);
				cursor += dataToCopy;
				outBuffCursor = outBuffEnd;
			} else { // Buffer ran out
				if(inBuffCursor < inBuffSize) {
					fillBuffers( inBuff.data(), inBuffCursor, inBuffSize, outBuff.data(),outBuffEnd,outBuff.size());
				} else {
					inBuffSize = inFront->read(inBuff.data(),inBuff.size());
					inBuffCursor = 0;
					if(!inBuffSize) return cursor;
				}
			}
		}
		return cursor;
	} else return 0;
}

Mode ProxyReadStream::getMode() const
{
	return Mode::READ;
}

bool ProxyReadStream::isValid() const
{
	if(inFront) return inFront->isValid();
	else return false;
}

}
}
