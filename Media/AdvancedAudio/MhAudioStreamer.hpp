#ifndef STREAMER_HPP
#define STREAMER_HPP
#include "MhAudioPlayable.hpp"
#include "MhAudioStatus.hpp"
#include "../Audio/MhSoundFile.hpp"

namespace MH33 {
namespace Audio {

class Streamer : public Playable
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
};

}
}

#endif // STREAMER_HPP
