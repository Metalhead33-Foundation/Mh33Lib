#include <iostream>
#include "Util/MhRNG.hpp"

int main(int argc, char *argv[])
{
	MH33::RNG rngesus;
	std::cout << "\nTesting integer RNG" << std::endl;
	for(int i = 0; i < 10; ++i) {
		std::cout << rngesus.generate() << " - ";
	}
	std::cout << "\nTesting floating-point RNG" << std::endl;
	for(int i = 0; i < 10; ++i) {
		std::cout << rngesus.generateFloat() << " - ";
	}
	return 0;
}
