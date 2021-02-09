#ifndef MIXER_HPP
#define MIXER_HPP
#include "MhAudioPlayable.hpp"
#include <map>
#include <vector>

namespace MH33 {
namespace Audio {

class Mixer : public Playable
{
public:
	const FrameCount frameCount;
	const FrameRate frameRate;
	const ChannelCount channelCount;
	typedef std::map<sPlayable,float> PlayableMap;
	typedef PlayableMap::iterator iterator;
	typedef PlayableMap::const_iterator const_iterator;
private:
	PlayableMap playables;
	std::vector<float> buffA,buffB;
	FrameCount process();
public:
	Mixer(FrameCount frameCount, FrameRate frameRate, ChannelCount channelCount);
	FrameCount outputTo(const Output& dst);
	FrameCount getFrameCount() const;
	FrameRate getFrameRate() const;
	ChannelCount getChannelCount() const;
	InterleavingType getInterleaving() const;
	// Map wrappers.
	bool empty() const;
	size_t size() const;
	void clear();
	std::pair<iterator,bool> set(const sPlayable& playable, float volume);
	std::pair<iterator,bool> set(sPlayable&& playable, float volume);
	iterator erase(iterator pos);
	iterator find(const sPlayable& playable);
	const_iterator find(const sPlayable& playable) const;
	iterator begin();
	const_iterator begin() const;
	iterator end();
	const_iterator end() const;
};

}
}
#endif // MIXER_HPP
