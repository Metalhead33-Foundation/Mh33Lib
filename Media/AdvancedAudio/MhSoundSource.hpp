#ifndef SOUNDSOURCE_HPP
#define SOUNDSOURCE_HPP
#include <Media/AdvancedAudio/MhAdvancedAudio.hpp>
#include <Media/AdvancedAudio/MhAudioPlayable.hpp>
#include <Media/AdvancedAudio/MhAudioStatus.hpp>
#include <Media/AdvancedAudio/MhAudioBuffer.hpp>

namespace MH33 {
namespace Audio {
class MH_ADV_AUDIO_API SoundSource : public Playable
{
private:
	sBuffer buffer;
	FrameIndex cursor;
	Status state;
	bool repeating;
public:
	SoundSource();
	SoundSource(const sBuffer &value);
	SoundSource(sBuffer&& value);
	FrameCount outputTo(const Output& dst);
	const sBuffer& getBuffer() const;
	sBuffer& getBuffer();
	void setBuffer(const sBuffer &value);
	void setBuffer(sBuffer&& value);
	FrameIndex getCursor() const;
	void setCursor(const FrameIndex &value);
	Status getState() const;
	void setState(const Status &value);
	bool getRepeating() const;
	void setRepeating(bool value);
	FrameRate getFrameRate() const;
	ChannelCount getChannelCount() const;
};

}
}
#endif // SOUNDSOURCE_HPP
