#ifndef MHCOMPRESSOR_HPP
#define MHCOMPRESSOR_HPP
#include "MhIoDevice.hpp"

namespace MH33 {
namespace Io {
class Compressor
{
private:
	void* handle;
	Device* input;
	Device* output;
	Util::Buffer inBuff;
	Util::Buffer outBuff;
	// No copy construction or assignment
	Compressor(const Compressor& cpy) = delete;
	Compressor& operator=(const Compressor& cpy) = delete;
public:
	// Move assignment and construction
	Compressor(Compressor&& mov);
	Compressor& operator=(Compressor&& mov);
	// Actual constructor and destructor
	Compressor();
	Compressor(Device* input, Device* output);
	~Compressor();
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
#endif // MHCOMPRESSOR_HPP
