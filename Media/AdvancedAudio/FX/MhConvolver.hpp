#ifndef MULTICHANNELCONVOLVER_HPP
#define MULTICHANNELCONVOLVER_HPP
#include "../MhAudioEffect.hpp"
#include "../../Audio/FFTConvolver/FFTConvolver.h"
#include <vector>
namespace MH33 {
namespace Audio {
namespace  FX {

class Convolver : public Effect
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
