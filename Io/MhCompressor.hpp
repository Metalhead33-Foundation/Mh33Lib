#ifndef MHCOMPRESSOR_HPP
#define MHCOMPRESSOR_HPP
#include "MhIoDevice.hpp"

namespace MH33 {
class Compressor
{
private:
	void* handle;
	IoDevice* input;
	IoDevice* output;
	Buffer inBuff;
	Buffer outBuff;
	// No copy construction or assignment
	Compressor(const Compressor& cpy) = delete;
	Compressor& operator=(const Compressor& cpy) = delete;
public:
	// Move assignment and construction
	Compressor(Compressor&& mov);
	Compressor& operator=(Compressor&& mov);
	// Actual constructor and destructor
	Compressor();
	Compressor(IoDevice* input, IoDevice* output);
	~Compressor();
	void compress();
	void setCompressionLevel(float value);
	//int getCompressionLevel() const;
	void setChecksum(bool value);
	//bool getChecksum() const;
	IoDevice *getInput() const;
	void setInput(IoDevice *value);
	IoDevice *getOutput() const;
	void setOutput(IoDevice *value);

	static void quickCompress(IoDevice& input, IoDevice& output, float compressionLevel = 0.5f, bool checksum = false);
};
}

#endif // MHCOMPRESSOR_HPP
