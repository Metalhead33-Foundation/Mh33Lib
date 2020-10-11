#ifndef MHPNG_HPP
#define MHPNG_HPP
#include <Io/MhIoDevice.hpp>
#include <memory>

namespace MH33 {
namespace GFX {

class Png
{
private:
	void *pngPtr, *infoPtr, *endInfoPtr;
	std::shared_ptr<IoDevice> iodev;
	bool ro;
	void initialize();
	// No copy constructor or assignment
	Png(const Png& cpy) = delete;
	Png& operator=(const Png& cpy) = delete;
public:
	// Move constructors and assignments
	Png(Png&& mov);
	Png& operator=(Png&& mov);
	// Actual constructors
	Png(void);
	Png(const std::shared_ptr<IoDevice>& dev);
	Png(std::shared_ptr<IoDevice>&& dev);

	void decode(uint16_t& width, uint16_t& height, uint8_t& color_type, uint8_t& bit_depth, Buffer& pixelData);
	void encode(uint16_t width, uint16_t height, uint8_t color_type, uint8_t bit_depth, Buffer &pixelData, int compressionLevel);
};

}
}

#endif // MHPNG_HPP
