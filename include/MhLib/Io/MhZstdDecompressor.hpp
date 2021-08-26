#ifndef MHZSTDDECOMPRESSOR_HPP
#define MHZSTDDECOMPRESSOR_HPP
#include <MhLib/Io/MhIoDevice.hpp>

namespace MH33 {
namespace Io {
class MH_IO_API ZstdDecompressor
{
private:
	void* handle;
	Device* input;
	Device* output;
	Util::Buffer inBuff;
	Util::Buffer outBuff;
	// No copy construction or assignment
	ZstdDecompressor(const ZstdDecompressor& cpy) = delete;
	ZstdDecompressor& operator=(const ZstdDecompressor& cpy) = delete;
public:
	// Move assignment and construction
	ZstdDecompressor(ZstdDecompressor&& mov);
	ZstdDecompressor& operator=(ZstdDecompressor&& mov);
	// Actual constructor and destructor
	ZstdDecompressor();
	ZstdDecompressor(Device* input, Device* output);
	~ZstdDecompressor();
	void decompress();
	Device *getInput() const;
	void setInput(Device *value);
	Device *getOutput() const;
	void setOutput(Device *value);

	static void qucikDecompress(Device &input, Device &output);
};
}
}

#endif // MHZSTDDECOMPRESSOR_HPP
