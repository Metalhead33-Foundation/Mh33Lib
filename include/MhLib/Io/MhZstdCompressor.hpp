#ifndef MHZSTDCOMPRESSOR_HPP
#define MHZSTDCOMPRESSOR_HPP
#include <MhLib/Io/MhIoDevice.hpp>

namespace MH33 {
namespace Io {
class MH_IO_API ZstdCompressor
{
private:
	void* handle;
	Device* input;
	Device* output;
	Util::Buffer inBuff;
	Util::Buffer outBuff;
	// No copy construction or assignment
	ZstdCompressor(const ZstdCompressor& cpy) = delete;
	ZstdCompressor& operator=(const ZstdCompressor& cpy) = delete;
public:
	// Move assignment and construction
	ZstdCompressor(ZstdCompressor&& mov);
	ZstdCompressor& operator=(ZstdCompressor&& mov);
	// Actual constructor and destructor
	ZstdCompressor();
	ZstdCompressor(Device* input, Device* output);
	~ZstdCompressor();
	void compress();
	void setCompressionLevel(float value);
	//int getCompressionLevel() const;
	void setChecksum(bool value);
	//bool getChecksum() const;
	Device *getInput() const;
	void setInput(Device *value);
	Device *getOutput() const;
	void setOutput(Device *value);

	static void quickCompress(Device& input, Device& output, float compressionLevel = 0.5f, bool checksum = false);
};
}
}
#endif // MHZSTDCOMPRESSOR_HPP
