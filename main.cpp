#include <iostream>
#include <SIMD/MhSIMD.hpp>
#include <Util/MhRNG.hpp>

int main(int argc, char *argv[])
{
	MH33::Util::RNG rng(31314);
	MH33::SIMD::Float32x8 avxa = { 0.5552f, 0.3452151f};
	MH33::SIMD::Float32x8 avxb;
	for(auto& it : avxb) {
		it = rng.generateFloat();
	}
	// avxa += avxb;
	for(const auto& it : avxa) {
		std::cout << it << std::endl;
	}
	return 0;
}

