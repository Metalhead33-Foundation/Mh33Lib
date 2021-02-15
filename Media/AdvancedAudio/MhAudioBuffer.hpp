#ifndef BUFFER_HPP
#define BUFFER_HPP
#include <Media/AdvancedAudio/MhAudioPacket.hpp>
#include <Media/Audio/MhSoundFile.hpp>
#include <vector>
#include <memory>
namespace MH33 {
namespace Audio {

class Buffer;
typedef std::shared_ptr<Buffer> sBuffer;
class Buffer
{
private:
	FrameCount frameCount;
	FrameRate frameRate;
	ChannelCount channelCount;
	std::vector<float> samples;
	void fillData(SoundFile& sndfile);
public:
	Buffer(const Io::sDevice& iodev);
	Buffer(Io::sDevice&& iodev);
	Buffer(Io::DeviceCreator iodev_creator, Io::Mode mode);
	Buffer(Io::System& iosys, const char* path, Io::Mode mode);
	Buffer(Io::System& iosys, const std::string& path, Io::Mode mode);
	void provideInput(Input& in, FrameIndex progress = FrameIndex(0));
	FrameCount getFrameCount() const;
	FrameRate getFrameRate() const;
	ChannelCount getChannelCount() const;
};

}
}
#endif // BUFFER_HPP
