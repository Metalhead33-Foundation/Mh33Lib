#include "MhTGA.hpp"

namespace MH33 {
namespace GFX {
namespace TGA {

void Header::load(IoDevice &input)
{
	DataStream<Endian::Little> tgaInput(input); // TGA is little-endian.

	auto currPos = tgaInput.tell();
	tgaInput.seek(SeekOrigin::END,26);
	tgaInput >> extensionOffset;
	tgaInput >> developerAreaOffset;
	char versionCheck[17] = "";
	tgaInput.read(versionCheck,16);
	version = 1;
	if ( strcmp( versionCheck, "TRUEVISION-XFILE" ) == 0 )
		version = 2;
	else {
		extensionOffset = -1;
		developerAreaOffset = -1;
	}
	tgaInput.seek(SeekOrigin::SET,currPos);

	tgaInput >> idLen;
	tgaInput >> colmapType;
	tgaInput >> imageType;
	tgaInput >> colorMapSpecification.firstEntryIndex;
	tgaInput >> colorMapSpecification.colorMapLength;
	tgaInput >> colorMapSpecification.colorMapEntrySize;
	tgaInput >> imageSpecification.xOrigin;
	tgaInput >> imageSpecification.yOrigin;
	tgaInput >> imageSpecification.width;
	tgaInput >> imageSpecification.height;
	tgaInput >> imageSpecification.pixelDepth;
	tgaInput >> imageSpecification.imageDescriptor;
	bool isCompressed = false;
	switch (imageType) {
	case 0:
		format = Format::INVALID;
		break;
	case 1:
		format = Format::PALETTIZED;
		break;
	case 2:
		format = Format::RGB;
		break;
	case 3:
		format = Format::GREYSCALE;
		break;
	case 9:
		format = Format::PALETTIZED;
		isCompressed = true;
		break;
	case 10:
		format = Format::RGB;
		isCompressed = true;
		break;
	case 11:
		format = Format::GREYSCALE;
		isCompressed = true;
		break;
	default:
		format = Format::INVALID;
		break;
	}
	tgaInput.seek(SeekOrigin::CUR,idLen); // Skip ID.
	if(colmapType) {
		size_t colMapSize = colorMapSpecification.colorMapLength * (colorMapSpecification.colorMapEntrySize / 8);
		colorMap.resize(colMapSize);
		tgaInput.read(colorMap.data(),colMapSize);
	}
	size_t imageSize = imageSpecification.width * imageSpecification.height * (imageSpecification.pixelDepth / 8);
	if(isCompressed) decodeCompressedImage(imageSize,tgaInput);
	else decodeImage(imageSize, tgaInput);
	const bool fliphoriz = (imageSpecification.imageDescriptor & 0x10) ? true : false;
	const bool flipvert = (imageSpecification.imageDescriptor & 0x20) ? false : true;
	if(flipvert) flipVert();
	if(fliphoriz) flipHoriz();
}

void Header::decodeImage(size_t imageSize, IoDevice& input)
{
	imageData.resize(imageSize);
	input.read(imageData.data(),imageSize); // Will read past the end of file in case of RLE.
}

void Header::decodeCompressedImage(size_t imageSize, IoDevice &input)
{
	imageData.resize(imageSize);
	input.read(imageData.data(),imageSize); // Will read past the end of file in case of RLE.
	Buffer tempImageData = imageData;
	int indexAccum = 0;
	int bytesPerPixel = ( imageSpecification.pixelDepth / 8 );
	int bytesPerPixelRLE = bytesPerPixel + 1;
	for ( int i = 0; indexAccum < imageSize; ) {
		int runCount = ( 127 & reinterpret_cast<uint8_t&>(tempImageData[i]) ) + 1;
		// Compressed data
		if ( 128 & reinterpret_cast<uint8_t&>(tempImageData[i]) ) {
			for ( int j = 0; j < runCount; j++ ) {
				for ( int k = 1; k < bytesPerPixelRLE; k++ ) {
					imageData[indexAccum++] = tempImageData[i + k];
				}
			}
			i += bytesPerPixelRLE;
		}
		// Raw data?
		else if ( !( 128 & reinterpret_cast<uint8_t&>(tempImageData[i]) ) ) {
			i++;
			for ( int j = 0; j < runCount; j++ ) {
				for ( int k = 0; k < bytesPerPixel; k++ ) {
					imageData[indexAccum++] = tempImageData[i + k];
				}
				i += bytesPerPixel;
			}
		}
	}
}

void Header::flipVert()
{
	const uint32_t stride = imageSpecification.width * (imageSpecification.pixelDepth / 8);
	Buffer reverseImage(imageData.size());
	for(uint32_t i = 0; i < imageSpecification.height; ++i) {
		memcpy(&reverseImage[stride*(imageSpecification.height-(i+1))], &imageData[i*stride], stride);
	}
	imageData = std::move(reverseImage);
	/*for(uint32_t i = 0; i < imageSpecification.height; ++i) {
		Buffer tmpbuffA(stride);
		Buffer tmpbuffB(stride);
		std::byte* ptrA = &imageData[stride*i];
		std::byte* ptrB = &imageData[stride*(imageSpecification.height-(i+1))];
		memcpy(tmpbuffA.data(),ptrA,stride);
		memcpy(tmpbuffB.data(),ptrB,stride);
		memcpy(ptrA,tmpbuffB.data(),stride);
		memcpy(ptrB,tmpbuffA.data(),stride);
	}*/
}

void Header::flipHoriz()
{
	const uint32_t stride = imageSpecification.width * (imageSpecification.pixelDepth / 8);
	for(uint32_t i = 0; i < imageSpecification.height; ++i) {
		std::byte* ptrA = &imageData[stride*i];
		switch (imageSpecification.pixelDepth) {
		case 8:
		{
			std::span<std::byte> spn(ptrA,stride);
			std::reverse(std::begin(spn),std::end(spn));
			break;
		}
		case 15:
		case 16:
		{
			std::span<uint16_t> spn(reinterpret_cast<uint16_t*>(ptrA),stride/2);
			std::reverse(std::begin(spn),std::end(spn));
			break;
		}
		case 24:
		{
			std::span<std::array<uint8_t,3>> spn(reinterpret_cast<std::array<uint8_t,3>*>(ptrA),stride/3);
			std::reverse(std::begin(spn),std::end(spn));
			break;
		}
		case 32:
		{
			std::span<uint32_t> spn(reinterpret_cast<uint32_t*>(ptrA),stride/4);
			std::reverse(std::begin(spn),std::end(spn));
			break;
		}
		default:
			break;
		}
	}
}

void Header::ExtensionInformation::load(DataStream<Endian::Little> &input)
{
	input >> extensionSize;
	input >> authorName;
	input >> authorComment;
	input >> timestamp;
	input >> jobId;
	input >> jobTime;
	input >> softwareID;
	input >> softwareVersion;
	input >> keyColour;
	input >> pixelAspectRatio;
	input >> gammaValue;
	input >> colourCorrectionOffset;
	input >> postageStampOffset;
	input >> scanlineOffset;
	input >> attributeType;
}

}
}
}
