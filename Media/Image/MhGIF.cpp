#include "MhGIF.hpp"
#include <gif_lib.h>
#include <memory>

namespace MH33 {
namespace GFX {
namespace GIF {

static int LATEST_ERROR;
static void CLOSE_GIF(GifFileType* ptr) { DGifCloseFile(ptr,&LATEST_ERROR); }
static int GIF_INPUT(GifFileType* container, GifByteType* buffer, int size)
{
	if(!container) return -1;
	IoDevice* filehandle = reinterpret_cast<IoDevice*>(container->UserData);
	if(!filehandle) return -1;
	return int(filehandle->read(buffer,size));
}
typedef std::unique_ptr<GifFileType, decltype (&CLOSE_GIF)> HandleType;

void decode(IoDevice &iodev, DecodeTarget &target)
{
	HandleType handle(DGifOpen(&iodev,&GIF_INPUT,&LATEST_ERROR),CLOSE_GIF);
	DGifSlurp(handle.get());
	int tmpFramerate = 0;
	target.transparentColorIndex = -1;
	for(int i = 0; i < handle->ExtensionBlockCount; ++i)
	{
		GraphicsControlBlock block;
		if (DGifExtensionToGCB(handle->ExtensionBlocks[i].ByteCount,handle->ExtensionBlocks[i].Bytes,
							   &block)) {
			if(block.TransparentColor > target.transparentColorIndex) target.transparentColorIndex = block.TransparentColor;
			if(block.DelayTime > tmpFramerate) tmpFramerate = block.DelayTime;
		}
	}
	target.delayTime = float(tmpFramerate) * 0.01f;
	target.width = handle->SWidth;
	target.height = handle->SHeight;
	ColorMapObject *gifcolormap = handle->SColorMap;
	if(!gifcolormap) return;
	GifColorType *gifpalette = gifcolormap->Colors;
	if(!gifpalette) return;
	target.palette.reserve(gifcolormap->ColorCount);
	for(int i = 0; i < gifcolormap->ColorCount; ++i) {
		target.palette.push_back( RGB<uint8_t>{ gifcolormap->Colors[i].Red, gifcolormap->Colors[i].Green, gifcolormap->Colors[i].Blue } );
	}
	target.frames.resize(handle->ImageCount);
	for(int i = 0; i < handle->ImageCount; ++i) {
		const SavedImage* img = &(handle->SavedImages[i]);
		const int newSize = img->ImageDesc.Height * img->ImageDesc.Width;
		std::vector<uint8_t> frame(newSize);
		for(int x = 0; x < newSize;++x) {
			frame[x] = img->RasterBits[x];
		}
		target.frames[i] = std::move(frame);
	}
}

}
}
}
