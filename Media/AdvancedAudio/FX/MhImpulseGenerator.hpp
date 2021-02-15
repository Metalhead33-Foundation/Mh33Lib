#ifndef MHIMPULSEGENERATOR_HPP
#define MHIMPULSEGENERATOR_HPP
#include <Media/AdvancedAudio/FX/MhConvolver.hpp>
namespace MH33 {
namespace Audio {
namespace  FX {

fftconvolver::sIrBuffer createLowpassFilter(FrameRate inputSamplerate,FrameRate CutoffFrequency, bool normalize=false);
fftconvolver::sIrBuffer createHighpassFilter(FrameRate inputSamplerate,FrameRate CutoffFrequency, bool normalize=false);
fftconvolver::sIrBuffer createBandpassFilter(FrameRate inputSamplerate,FrameRate lowCutoff, FrameRate highCutoff, bool normalize=false);
fftconvolver::sIrBuffer createBandrejectFilter(FrameRate inputSamplerate,FrameRate lowCutoff, FrameRate highCutoff, bool normalize=false);
fftconvolver::sIrBuffer createDelay(FrameRate inputSamplerate, SampleIndex sampleOffset, float delayVolume=1.0f);

}
}
}

#endif // MHIMPULSEGENERATOR_HPP
