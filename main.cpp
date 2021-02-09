#include <iostream>
#include <Gimmick/MhWordGenerator.hpp>
#include <ctime>
#include "Util/MhClock.hpp"

int main(int argc, char *argv[])
{
	MH33::Util::Clock clock;
	MH33::Gimmick::WordGenerator wordgen(time(nullptr));
	std::cout << "Welcome to " << wordgen.generate(3,12,MH33::Gimmick::CapitalizationPolicy::START) << std::endl;
	std::cout << "This took " << std::fixed << clock.elapsed().getSeconds() << " seconds." << std::endl;
	return 0;
}

