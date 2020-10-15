#ifndef MHRNG_HPP
#define MHRNG_HPP
#include <cstdint>
namespace MH33 {

class RNG
{
private:
	uint32_t seed;
public:
	RNG(uint32_t seed=0);
	uint32_t getSeed() const;
	void setSeed(uint32_t value);

	uint32_t generate();
	float generateFloat();
	double generateDouble();

	uint32_t generate(uint32_t max);
	float generateFloat(float max);
	double generateDouble(double max);

	uint32_t generate(uint32_t min, uint32_t max);
	float generateFloat(float min, float max);
	double generateDouble(double min, double max);
};

}
#endif // MHRNG_HPP
