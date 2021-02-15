#ifndef MHDECOMPRESSOR_HPP
#define MHDECOMPRESSOR_HPP
#include <Io/MhIoDevice.hpp>

namespace MH33 {
namespace Io {
class Decompressor
{
private:
	void* handle;
	Device* input;
	Device* output;
	Util::Buffer inBuff;
	Util::Buffer outBuff;
	// No copy construction or assignment
	Decompressor(const Decompressor& cpy) = delete;
	Decompressor& operator=(const Decompressor& cpy) = delete;
public:
	// Move assignment and construction
	Decompressor(Decompressor&& mov);
	Decompressor& operator=(Decompressor&& mov);
	// Actual constructor and destructor
	Decompressor();
	Decompressor(Device* input, Device* output);
	~Decompressor();
	void decompress();
	Device *getInput() const;
	void setInput(Device *value);
	Device *getOutput() const;
	void setOutput(Device *value);

	static void qucikDecompress(Device &input, Device &output);
};
}
}

#endif // MHDECOMPRESSOR_HPP
