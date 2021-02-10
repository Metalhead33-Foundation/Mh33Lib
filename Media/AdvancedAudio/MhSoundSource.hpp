#ifndef SOUNDSOURCE_HPP
#define SOUNDSOURCE_HPP
#include "MhAudioPlayable.hpp"
#include "MhAudioStatus.hpp"
#include "MhAudioBuffer.hpp"

namespace MH33 {
namespace Audio {
class SoundSource : public Playable
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
