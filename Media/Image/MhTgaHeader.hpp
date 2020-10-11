#ifndef MHTGAHEADER_HPP
#define MHTGAHEADER_HPP
#include <Io/MhDataStream.hpp>

namespace MH33 {
namespace GFX {

enum TgaFormat {
	INVALID = 0x00,
	RGB = 0x01,
	GREYSCALE = 0x02,
	PALETTIZED = 0x03
};

struct TgaHeader {
public:
	// Read information - straight from the file
	uint8_t idLen;
	uint8_t colmapType;
	uint8_t imageType;
	struct {
		uint16_t firstEntryIndex;
		uint16_t colorMapLength;
		uint8_t colorMapEntrySize;
	} colorMapSpecification;
	struct {
		uint16_t xOrigin;
		uint16_t yOrigin;
		uint16_t width;
		uint16_t height;
		uint8_t pixelDepth;
		uint8_t imageDescriptor;
	} imageSpecification;
	int32_t extensionOffset;
	int32_t developerAreaOffset;
	struct ExtensionInformation {
		uint16_t extensionSize;
		std::array<char,41> authorName;
		std::array<char,324> authorComment;
		std::array<uint16_t,6> timestamp;
		std::array<char,41> jobId;
		std::array<uint16_t,3> jobTime;
		std::array<char,41> softwareID;
		std::array<char,3> softwareVersion;
		uint32_t keyColour;
		std::array<uint16_t,2> pixelAspectRatio;
		std::array<uint16_t,2> gammaValue;
		uint32_t colourCorrectionOffset;
		uint32_t postageStampOffset;
		uint32_t scanlineOffset;
		uint8_t attributeType;
		void load(DataStream<Endian::Little>& input);
	};
	// Deduced information - deduced from read info
	int version;
	TgaFormat format;
	std::vector<std::byte> colorMap;
	std::vector<std::byte> imageData;
	// Commands
	void load(IoDevice& input);
private:
	void decodeImage(size_t imageSize, IoDevice& input);
	void decodeCompressedImage(size_t imageSize, IoDevice& input);
};

}
}
#endif // MHTGAHEADER_HPP
