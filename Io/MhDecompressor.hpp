#ifndef MHDECOMPRESSOR_HPP
#define MHDECOMPRESSOR_HPP
#include "MhIoDevice.hpp"

namespace MH33 {
class Decompressor
{
private:
	void* handle;
	IoDevice* input;
	IoDevice* output;
	Buffer inBuff;
	Buffer outBuff;
	// No copy construction or assignment
	Decompressor(const Decompressor& cpy) = delete;
	Decompressor& operator=(const Decompressor& cpy) = delete;
public:
	// Move assignment and construction
	Decompressor(Decompressor&& mov);
	Decompressor& operator=(Decompressor&& mov);
	// Actual constructor and destructor
	Decompressor();
	Decompressor(IoDevice* input, IoDevice* output);
	~Decompressor();
	void decompress();
	IoDevice *getInput() const;
	void setInput(IoDevice *value);
	IoDevice *getOutput() const;
	void setOutput(IoDevice *value);

	static void qucikDecompress(IoDevice &input, IoDevice &output);
};
}

#endif // MHDECOMPRESSOR_HPP
