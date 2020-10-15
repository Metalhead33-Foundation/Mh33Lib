#include "MhModuleRenderer.hpp"
#include <libopenmpt/libopenmpt.h>

size_t vfio_openmpt_read( void *stream, void *dst, size_t bytes );
int vfio_openmpt_seek( void *stream, int64_t offset, int whence );
int64_t vfio_openmpt_tell( void *stream );

static openmpt_stream_callbacks OpenmptIO = {
	vfio_openmpt_read, vfio_openmpt_seek, vfio_openmpt_tell };
namespace MH33 {
namespace Audio {
#define MODULE_HDNL reinterpret_cast<openmpt_module*>(handle)

ModuleRenderer::ModuleRenderer(ModuleRenderer &&mov): handle(mov.handle), iodev(std::move(mov.iodev))
{

}

ModuleRenderer &ModuleRenderer::operator=(ModuleRenderer &&mov)
{
	if(handle) openmpt_module_destroy(MODULE_HDNL);
	this->handle = mov.handle;
	mov.handle = nullptr;
	this->iodev = std::move(mov.iodev);
	return *this;
}

ModuleRenderer::~ModuleRenderer()
{
	if(handle) openmpt_module_destroy(MODULE_HDNL);
}

ModuleRenderer::ModuleRenderer(const sIoDevice &iodev) : handle(nullptr), iodev(iodev)
{
	if(this->iodev) {
		handle = openmpt_module_create2(OpenmptIO,this->iodev.get(),nullptr,
										nullptr, nullptr, nullptr, nullptr,
										nullptr, nullptr);
	}
}

ModuleRenderer::ModuleRenderer(sIoDevice &&iodev) : handle(nullptr), iodev(std::move(iodev))
{
	if(this->iodev) {
		handle = openmpt_module_create2(OpenmptIO,this->iodev.get(),nullptr,
										nullptr, nullptr, nullptr, nullptr,
										nullptr, nullptr);
	}
}

ModuleRenderer::ModuleRenderer(const IoDeviceCreator &iodev_creator, IoMode mode) : handle(nullptr), iodev(iodev_creator(mode))
{
	if(this->iodev) {
		handle = openmpt_module_create2(OpenmptIO,this->iodev.get(),nullptr,
										nullptr, nullptr, nullptr, nullptr,
										nullptr, nullptr);
	}
}
// Getters and setters
void ModuleRenderer::setSubsong( int32_t subsong ) {
	openmpt_module_select_subsong(MODULE_HDNL,subsong);
}
int32_t ModuleRenderer::getSubsong( ) const {
	return openmpt_module_get_selected_subsong(MODULE_HDNL);
}
void ModuleRenderer::setRepeating( bool value ) {
	openmpt_module_set_repeat_count(MODULE_HDNL, value ? -1 : 0);
}
bool ModuleRenderer::isRepeating( ) const {
	return openmpt_module_get_repeat_count(MODULE_HDNL) != 0;
}
double ModuleRenderer::getDuration( ) const {
	return openmpt_module_get_duration_seconds(MODULE_HDNL);
}
double ModuleRenderer::setPosition( double seconds ) {
	return openmpt_module_set_position_seconds(MODULE_HDNL,seconds);
}
double ModuleRenderer::getPosition( ) const {
	return openmpt_module_get_position_seconds(MODULE_HDNL);
}
void ModuleRenderer::setMasterGain(int32_t	value ) {
	openmpt_module_set_render_param( MODULE_HDNL, OPENMPT_MODULE_RENDER_MASTERGAIN_MILLIBEL, value);
} // set_render_param(OPENMPT_MODULE_RENDER_MASTERGAIN_MILLIBEL)
int32_t ModuleRenderer::getMasterGain( ) const {
	int32_t val;
	openmpt_module_get_render_param(MODULE_HDNL,OPENMPT_MODULE_RENDER_MASTERGAIN_MILLIBEL,&val);
	return val;
} // get_render_param(OPENMPT_MODULE_RENDER_MASTERGAIN_MILLIBEL)
void ModuleRenderer::setStereoSeparation(int32_t value ) {
	openmpt_module_set_render_param( MODULE_HDNL, OPENMPT_MODULE_RENDER_STEREOSEPARATION_PERCENT, value);
} // set_render_param(OPENMPT_MODULE_RENDER_STEREOSEPARATION_PERCENT)
int32_t ModuleRenderer::getStereoSeparation( ) const {
	int32_t val;
	openmpt_module_get_render_param(MODULE_HDNL,OPENMPT_MODULE_RENDER_STEREOSEPARATION_PERCENT,&val);
	return val;
} // get_render_param(OPENMPT_MODULE_RENDER_STEREOSEPARATION_PERCENT)
void ModuleRenderer::setInterpolationFilter(int32_t	value ) {
	openmpt_module_set_render_param( MODULE_HDNL, OPENMPT_MODULE_RENDER_INTERPOLATIONFILTER_LENGTH, value);
} // set_render_param(OPENMPT_MODULE_RENDER_INTERPOLATIONFILTER_LENGTH)
int32_t ModuleRenderer::getInterpolationFilter( ) const {
	int32_t val;
	openmpt_module_get_render_param(MODULE_HDNL,OPENMPT_MODULE_RENDER_INTERPOLATIONFILTER_LENGTH,&val);
	return val;
} // get_render_param(OPENMPT_MODULE_RENDER_INTERPOLATIONFILTER_LENGTH)
void ModuleRenderer::setVolumeRamping(int32_t value ) {
	openmpt_module_set_render_param( MODULE_HDNL, OPENMPT_MODULE_RENDER_VOLUMERAMPING_STRENGTH, value);
} // set_render_param(OPENMPT_MODULE_RENDER_VOLUMERAMPING_STRENGTH)
int32_t ModuleRenderer::getVolumeRamping( )	const {
	int32_t val;
	openmpt_module_get_render_param(MODULE_HDNL,OPENMPT_MODULE_RENDER_VOLUMERAMPING_STRENGTH,&val);
	return val;
} // get_render_param(OPENMPT_MODULE_RENDER_VOLUMERAMPING_STRENGTH)
// Metadata
const char* ModuleRenderer::getType( ) const {
	return openmpt_module_get_metadata(MODULE_HDNL,"type");
}         // get_metadata('type')
const char* ModuleRenderer::getTypeLong( ) const {
	return openmpt_module_get_metadata(MODULE_HDNL,"type_long");
}     // get_metadata('type_long')
const char* ModuleRenderer::getOriginalType( ) const {
	return openmpt_module_get_metadata(MODULE_HDNL,"originaltype");
} // get_metadata('originaltype')
const char* ModuleRenderer::getOriginalTypeLong( ) const {
	return openmpt_module_get_metadata(MODULE_HDNL,"originaltype_long");
}      // get_metadata('originaltype_long')
const char* ModuleRenderer::getContainer( ) const {
	return openmpt_module_get_metadata(MODULE_HDNL,"container");
} // get_metadata('container')
const char* ModuleRenderer::getContainerLong( ) const {
	return openmpt_module_get_metadata(MODULE_HDNL,"container_long");
} // get_metadata('container_long')
const char* ModuleRenderer::getTracker( ) const {
	return openmpt_module_get_metadata(MODULE_HDNL,"tracker");
}       // get_metadata('tracker')
const char* ModuleRenderer::getArtist( ) const {
	return openmpt_module_get_metadata(MODULE_HDNL,"artist");
}        // get_metadata('artist')
const char* ModuleRenderer::getTitle( ) const {
	return openmpt_module_get_metadata(MODULE_HDNL,"title");
}         // get_metadata('title')
const char* ModuleRenderer::getDate( ) const {
	return openmpt_module_get_metadata(MODULE_HDNL,"date");
}          // get_metadata('date')
// Rendering
FrameCount ModuleRenderer::readMono(FrameRate framerate, FrameCount frames, int16_t *mono ) {
	return FrameCount(openmpt_module_read_mono(MODULE_HDNL,framerate.var,frames.var,mono));
}
FrameCount ModuleRenderer::readMono( FrameRate framerate, FrameCount frames, float *mono ) {
	return FrameCount(openmpt_module_read_float_mono(MODULE_HDNL,framerate.var,frames.var,mono));
}
FrameCount ModuleRenderer::readStereo(FrameRate framerate, FrameCount frames, int16_t *left, int16_t *right ) {
	return FrameCount(openmpt_module_read_stereo(MODULE_HDNL,framerate.var,frames.var,left,right));
}
FrameCount ModuleRenderer::readStereo( FrameRate framerate, FrameCount frames, float *left, float *right ) {
	return FrameCount(openmpt_module_read_float_stereo(MODULE_HDNL,framerate.var,frames.var,left,right));
}
FrameCount ModuleRenderer::readQuad( FrameRate framerate, FrameCount frames, int16_t *left,
								int16_t *right, int16_t *rear_left,	int16_t *rear_right ) {
	return FrameCount(openmpt_module_read_quad(MODULE_HDNL,framerate.var,frames.var,left,right,rear_left,rear_right));
}
FrameCount ModuleRenderer::readQuad( FrameRate framerate, FrameCount frames, float *left,
								float *right, float *rear_left, float *rear_right ) {
	return FrameCount(openmpt_module_read_float_quad(MODULE_HDNL,framerate.var,frames.var,left,right,rear_left,rear_right));
}
FrameCount ModuleRenderer::readInterleavedStereo( FrameRate framerate, FrameCount frames, int16_t *interleaved_stereo ) {
	return FrameCount(openmpt_module_read_interleaved_stereo(MODULE_HDNL,framerate.var,frames.var,interleaved_stereo));
}
FrameCount ModuleRenderer::readInterleavedStereo( FrameRate framerate, FrameCount frames, float *interleaved_stereo ) {
	return FrameCount(openmpt_module_read_interleaved_float_stereo(MODULE_HDNL,framerate.var,frames.var,interleaved_stereo));
}
FrameCount ModuleRenderer::readInterleavedQuad( FrameRate framerate, FrameCount frames, int16_t *interleaved_quad ) {
	return FrameCount(openmpt_module_read_interleaved_quad(MODULE_HDNL,framerate.var,frames.var,interleaved_quad));
}
FrameCount ModuleRenderer::readInterleavedQuad( FrameRate framerate, FrameCount frames, float *interleaved_quad ) {
	return FrameCount(openmpt_module_read_interleaved_float_quad(MODULE_HDNL,framerate.var,frames.var,interleaved_quad));
}


}
}

size_t vfio_openmpt_read( void *stream, void *dst, size_t bytes ) {
	return size_t( reinterpret_cast< MH33::IoDevice* >( stream )->read(
		dst, int64_t( bytes ) ) );
}
int vfio_openmpt_seek( void *stream, int64_t offset, int whence ) {
	MH33::IoDevice* chandle = reinterpret_cast< MH33::IoDevice* >( stream );
	switch ( whence ) {
	case OPENMPT_STREAM_SEEK_SET:
		chandle->seek( MH33::SeekOrigin::SET, offset ); return chandle->tell() ? 0 : -1;
	case OPENMPT_STREAM_SEEK_CUR:
		chandle->seek( MH33::SeekOrigin::CUR, offset ); return chandle->tell() ? 0 : -1;
	case OPENMPT_STREAM_SEEK_END:
		chandle->seek( MH33::SeekOrigin::END, offset ); return chandle->tell() ? 0 : -1;
	default:
		return -1;
	}
}
int64_t vfio_openmpt_tell( void *stream ) {
	return int64_t( reinterpret_cast< MH33::IoDevice* >( stream )->tell( ) );
}
