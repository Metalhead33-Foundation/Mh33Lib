#include "MhAudioMixer.hpp"
#include <cstring>
#include "MhAudioError.hpp"
namespace MH33 {
namespace Audio {

FrameCount Mixer::process()
{
	memset(this->buffA.data(),0,sizeof(float)*this->buffA.size());
	FrameCount largest(0);
	Output out;
	out.dst = this->buffB.data();
	out.channels = this->channelCount;
	out.framerate = this->frameRate;
	out.frameCount = this->frameCount;
	out.interleaving = InterleavingType::INTERLEAVED;
	for(auto it = std::begin(playables); it != std::end(playables); ++it) {
		FrameCount processed = it->first->outputTo(out);
		largest = std::max(largest,processed);
		for(const auto jt : processed) {
			const float * const inFrameStart = &buffB[jt * channelCount.var];
			float * const outFrameStart = &buffA[jt * channelCount.var];
			for(const auto zt : channelCount) {
				outFrameStart[zt] += inFrameStart[zt] * it->second;
			}
		}
	}
	return largest;
}

Mixer::Mixer(FrameCount frameCount, FrameRate frameRate, ChannelCount channelCount)
	: frameCount(frameCount), frameRate(frameRate), channelCount(channelCount),
	  buffA(framesToSamples(frameCount,channelCount).var), buffB(framesToSamples(frameCount,channelCount).var)
{

}

FrameCount Mixer::outputTo(const Output &dst)
{
	if(dst.channels != this->channelCount) throw ChannelCountMismatchError(dst.channels,this->channelCount);
	if(dst.framerate != this->frameRate) throw FrameratetMismatchError(dst.framerate,this->frameRate);
	if(channelCount.var > 1 && dst.interleaving != InterleavingType::INTERLEAVED) throw InterleavingMismatchError(dst.interleaving,InterleavingType::INTERLEAVED);
	FrameCount processed = process();
	memcpy(dst.dst,buffA.data(),samplesToBytes(framesToSamples(processed,channelCount)));
	return processed;
}

bool Mixer::empty() const { return playables.empty(); }
size_t Mixer::size() const { return playables.size(); }
void Mixer::clear() { playables.clear(); }
std::pair<Mixer::iterator,bool> Mixer::set(const sPlayable& playable, float volume) {
	return playables.insert_or_assign(playable,volume);
}
std::pair<Mixer::iterator,bool> Mixer::set(sPlayable&& playable, float volume) {
	return playables.insert_or_assign(playable,volume);
}
Mixer::iterator Mixer::erase(iterator pos) {
	return playables.erase(pos);
}
Mixer::iterator Mixer::find(const sPlayable& playable) {
	return playables.find(playable);
}
Mixer::const_iterator Mixer::find(const sPlayable& playable) const {
	return playables.find(playable);
}
Mixer::iterator Mixer::begin() { return playables.begin(); }
Mixer::const_iterator Mixer::begin() const { return playables.begin(); }
Mixer::iterator Mixer::end() { return playables.end(); }
Mixer::const_iterator Mixer::end() const { return playables.end(); }

}
}
