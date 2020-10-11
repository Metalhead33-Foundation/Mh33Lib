#ifndef MHDDSHEADER_HPP
#define MHDDSHEADER_HPP
#include <Io/MhDataStream.hpp>

namespace MH33 {
namespace GFX {

enum DdsType {
	INVALID = 0,
	DXT1,
	DXT3,
	DXT5,
	DX10
};

struct DdsHeader
{
	// We read this from the file
	uint32_t dwSize;
	uint32_t dwFlags;
	uint32_t dwHeight;
	uint32_t dwWidth;
	uint32_t dwPitchOrLinearSize;
	uint32_t dwDepth;
	uint32_t dwMipMapCount;
	std::array<uint32_t,11> dwReserved1;
	struct {
		uint32_t dwSize;
		uint32_t dwFlags;
		uint32_t dwFourCC;
		uint32_t dwRGBBitCount;
		uint32_t dwRBitMask;
		uint32_t dwGBitMask;
		uint32_t dwBBitMask;
		uint32_t dwABitMask;
	} ddspf;
	uint32_t dwCaps;
	uint32_t dwCaps2;
	uint32_t dwCaps3;
	uint32_t dwCaps4;
	uint32_t dwReserved2;
	// This part is optional
	struct {
		uint32_t dxgiFormat;
		uint32_t resourceDimension;
		uint32_t miscFlag;
		uint32_t arraySize;
		uint32_t miscFlags2;
	} headerDXT10;
	// We infer this from the file
	DdsType type;
	struct Mipmap {
		uint32_t width, height;
		std::vector<std::byte> bytes;
	};
	std::vector<Mipmap> mipmaps;
	void load(IoDevice& input);
};

}
}
#endif // MHDDSHEADER_HPP
