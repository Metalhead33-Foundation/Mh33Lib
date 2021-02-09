#include "MhAudioStreamer.hpp"
#include "MhAudioError.hpp"

namespace MH33 {
namespace Audio {

const SoundFile &Streamer::getSoundfile() const
{
	return soundfile;
}

SoundFile &Streamer::getSoundfile()
{
	return soundfile;
}

FrameCount Streamer::outputTo(const Output &dst)
{
	if(state != Status::PLAYING) return FrameCount(0);
	if(dst.channels != soundfile.getChannels()) throw ChannelCountMismatchError(dst.channels,soundfile.getChannels());
	if(dst.framerate != soundfile.getFrameRate()) throw FrameratetMismatchError(dst.framerate,soundfile.getFrameRate());
	if(dst.channels.var > 1 && dst.interleaving != InterleavingType::INTERLEAVED) throw InterleavingMismatchError(dst.interleaving,InterleavingType::INTERLEAVED);
	FrameCount toReturn = soundfile.readf(dst.dst,dst.frameCount);
	if(!toReturn.var) {
		if(!repeating) state = Status::STOPPED;
		soundfile.seekSet(FrameCount(0));
	}
	return toReturn;
}

Status Streamer::getState() const
{
	return state;
}

void Streamer::setState(const Status &value)
{
	state = value;
	if(state == Status::STOPPED) soundfile.seekSet(FrameCount(0));
}

bool Streamer::getRepeating() const
{
	return repeating;
}

void Streamer::setRepeating(bool value)
{
	repeating = value;
}

Streamer::Streamer(const Io::sDevice &iodev)
	: soundfile(iodev), state(Status::STOPPED), repeating(false)
{

}

Streamer::Streamer(Io::sDevice &&iodev)
	: soundfile(std::move(iodev)), state(Status::STOPPED), repeating(false)
{

}

Streamer::Streamer(Io::DeviceCreator iodev_creator, Io::Mode mode)
	: soundfile(iodev_creator,mode), state(Status::STOPPED), repeating(false)
{

}

Streamer::Streamer(Io::System &iosys, const char *path, Io::Mode mode)
	: soundfile(iosys,path,mode), state(Status::STOPPED), repeating(false)
{

}

Streamer::Streamer(Io::System &iosys, const std::string &path, Io::Mode mode)
	: soundfile(iosys,path,mode), state(Status::STOPPED), repeating(false)
{

}


}
}
