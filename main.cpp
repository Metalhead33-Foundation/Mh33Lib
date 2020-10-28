#include <iostream>
#include <SIMD/MhSIMD.hpp>
#include <Util/MhRNG.hpp>

int main(int argc, char *argv[])
{
	MH33::Util::RNG rng(31314);
	MH33::SIMD::Float32x8 avxa;
	MH33::SIMD::Float32x8 avxb;
	for(auto& it : avxa) {
		it = rng.generateFloat();
	}
	for(auto& it : avxb) {
		it = rng.generateFloat();
	}
	avxa += avxb;
	for(const auto& it : avxa) {
		std::cout << it << std::endl;
	}
	return 0;
}

