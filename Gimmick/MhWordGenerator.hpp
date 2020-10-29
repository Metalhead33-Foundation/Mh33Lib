#ifndef WORDGENERATOR_HPP
#define WORDGENERATOR_HPP
#include <Util/MhRNG.hpp>

namespace MH33 {
namespace Gimmick {

enum class CapitalizationPolicy {
	DONT,
	ALL,
	START
};

class WordGenerator
{
private:
	Util::RNG rng;
public:
	WordGenerator(uint32_t seed = 0);
	WordGenerator(const Util::RNG& nrng);
	WordGenerator(const WordGenerator& cpy);
	std::string generate(unsigned minLength, unsigned maxLength, CapitalizationPolicy capitalizationPolicy = CapitalizationPolicy::DONT);
};

}
}

#endif // WORDGENERATOR_HPP
