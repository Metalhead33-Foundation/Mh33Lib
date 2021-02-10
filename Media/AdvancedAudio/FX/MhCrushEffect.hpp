#ifndef CRUSHEFFECT_HPP
#define CRUSHEFFECT_HPP
#include "SampleLevelEffect.hpp"
namespace MH33 {
namespace Audio {
namespace  FX {

class CrushEffect : public SampleLevelEffect
{
private:
	float maxLevel;
protected:
	float doSampleLevelEffect(float input) const;
public:
	CrushEffect(float maxLevel);
	float getMaxLevel() const;
	void setMaxLevel(float value);
};

}
}
}
#endif // CRUSHEFFECT_HPP
