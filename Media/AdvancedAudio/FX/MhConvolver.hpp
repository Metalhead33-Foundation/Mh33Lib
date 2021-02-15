#ifndef MULTICHANNELCONVOLVER_HPP
#define MULTICHANNELCONVOLVER_HPP
#include <Media/AdvancedAudio/MhAdvancedAudio.hpp>
#include <Media/AdvancedAudio/MhAudioEffect.hpp>
#include <Media/Audio/FFTConvolver/FFTConvolver.h>
#include <vector>
namespace MH33 {
namespace Audio {
namespace  FX {

class MH_ADV_AUDIO_API Convolver : public Effect
{
public:
	const ChannelCount channels;
private:
	std::vector<fftconvolver::FFTConvolver> convolvers;
public:
	Convolver(ChannelCount channels);
	void doEffect(const ModificationStream& modstream);
	bool requiresDeinterlacing();
	const fftconvolver::sIrBuffer getBuffer(ChannelIndex channel) const;
	void setBuffer(ChannelIndex channel, fftconvolver::sIrBuffer buffer);
};
}
}
}

#endif // MULTICHANNELCONVOLVER_HPP
