#ifndef MHZFLATOR_HPP
#define MHZFLATOR_HPP
#include <MhLib/Io/MhIoDevice.hpp>

namespace MH33 {
namespace Io {
class MH_IO_API ZFlator
{
private:
	Device* input;
	Device* output;
	Util::Buffer inBuff;
	Util::Buffer outBuff;
	// No copy construction or assignment
	ZFlator(const ZFlator& cpy) = delete;
	ZFlator& operator=(const ZFlator& cpy) = delete;
public:
	// Move assignment and construction
	ZFlator(ZFlator&& mov);
	ZFlator& operator=(ZFlator&& mov);
	// Actual constructor and destructor
	ZFlator();
	ZFlator(Device* input, Device* output);
	~ZFlator();
	void decompress();
	void compress(int level);
	Device *getInput() const;
	void setInput(Device *value);
	Device *getOutput() const;
	void setOutput(Device *value);

	static void quickDecompress(Device &input, Device &output);
	static void quickCompress(Device &input, Device &output);
};
}
}

#endif // MHZFLATOR_HPP
