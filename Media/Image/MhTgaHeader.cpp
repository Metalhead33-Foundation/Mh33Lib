#include "MhTgaHeader.hpp"
namespace MH33 {
namespace GFX {

void TgaHeader::load(IoDevice &input)
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
		format = TgaFormat::INVALID;
		break;
	case 1:
		format = TgaFormat::PALETTIZED;
		break;
	case 2:
		format = TgaFormat::RGB;
		break;
	case 3:
		format = TgaFormat::GREYSCALE;
		break;
	case 9:
		format = TgaFormat::PALETTIZED;
		isCompressed = true;
		break;
	case 10:
		format = TgaFormat::RGB;
		isCompressed = true;
		break;
	case 11:
		format = TgaFormat::GREYSCALE;
		isCompressed = true;
		break;
	default:
		format = TgaFormat::INVALID;
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
}

void TgaHeader::decodeImage(size_t imageSize, IoDevice& input)
{
	imageData.resize(imageSize);
	input.read(imageData.data(),imageSize); // Will read past the end of file in case of RLE.
}

void TgaHeader::decodeCompressedImage(size_t imageSize, IoDevice &input)
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

void TgaHeader::ExtensionInformation::load(DataStream<Endian::Little> &input)
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
