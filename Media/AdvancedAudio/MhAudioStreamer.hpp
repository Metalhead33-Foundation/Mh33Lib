#ifndef STREAMER_HPP
#define STREAMER_HPP
#include <Media/AdvancedAudio/MhAdvancedAudio.hpp>
#include <Media/AdvancedAudio/MhAudioPlayable.hpp>
#include <Media/AdvancedAudio/MhAudioStatus.hpp>
#include "../Audio/MhSoundFile.hpp"

namespace MH33 {
namespace Audio {

class MH_ADV_AUDIO_API Streamer : public Playable
{
private:
	SoundFile soundfile;
	Status state;
	bool repeating;
public:
	Streamer(const Io::sDevice& iodev);
	Streamer(Io::sDevice&& iodev);
	Streamer(Io::DeviceCreator iodev_creator, Io::Mode mode);
	Streamer(Io::System& iosys, const char* path, Io::Mode mode);
	Streamer(Io::System& iosys, const std::string& path, Io::Mode mode);
	const SoundFile& getSoundfile() const;
	SoundFile& getSoundfile();
	FrameCount outputTo(const Output& dst);
	Status getState() const;
	void setState(const Status &value);
	bool getRepeating() const;
	void setRepeating(bool value);
	FrameRate getFrameRate() const;
	ChannelCount getChannelCount() const;
};

}
}

#endif // STREAMER_HPP
