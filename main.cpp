#include <iostream>
#include <Gimmick/MhWordGenerator.hpp>
#include <ctime>

int main(int argc, char *argv[])
{
	MH33::Gimmick::WordGenerator wordgen(time(nullptr));
	std::cout << "Welcome to " << wordgen.generate(3,12,MH33::Gimmick::CapitalizationPolicy::START) << std::endl;
	return 0;
}

