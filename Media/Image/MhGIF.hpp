#ifndef GIF_HPP
#define GIF_HPP
#include <Io/MhIoDevice.hpp>
#include "MhRGB.hpp"

namespace MH33 {
namespace GFX {
namespace GIF {

struct DecodeTarget {
	std::vector<std::vector<uint8_t>> frames;
	std::vector<RGB<uint8_t>> palette;
	unsigned width,height;
	float delayTime;
	int transparentColorIndex;
};
void decode(IoDevice& iodev, DecodeTarget& target);

}
}
}
#endif // GIF_HPP
