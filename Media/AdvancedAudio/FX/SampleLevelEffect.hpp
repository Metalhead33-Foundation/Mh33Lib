#ifndef SAMPLELEVELEFFECT_HPP
#define SAMPLELEVELEFFECT_HPP
#include "../MhAudioEffect.hpp"
namespace MH33 {
namespace Audio {
namespace  FX {

class SampleLevelEffect : public Effect {
protected:
	virtual float doSampleLevelEffect(float input) const = 0;
public:
	virtual ~SampleLevelEffect() = default;
	void doEffect(const ModificationStream& modstream);
};

}
}
}
#endif // SAMPLELEVELEFFECT_HPP
