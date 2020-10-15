#include <iostream>
#include "Util/MhRNG.hpp"

int main(int argc, char *argv[])
{
	MH33::RNG rngesus;
	std::string randomstring("Whatever, I'm just going on a tangent here.");
	for(const auto& it : randomstring) {
		std::cout << rngesus.pick(randomstring);
	}
	std::cout << std::endl;
	return 0;
}
