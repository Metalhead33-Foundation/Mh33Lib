#include "MhClampEffect.hpp"
#include "../../../Util/MhEndianness.hpp"

namespace MH33 {
namespace Audio {
namespace  FX {

ClampEffect::ClampEffect(float maximumLevel) : maximumLevel(maximumLevel)
{

}

float ClampEffect::getMaximumLevel() const
{
	return maximumLevel;
}

void ClampEffect::setMaximumLevel(float value)
{
	maximumLevel = value;
}

float ClampEffect::doSampleLevelEffect(float input) const
{
	return Util::sign(input) * (std::min(std::abs(input),maximumLevel) / maximumLevel);
}

}
}
}
