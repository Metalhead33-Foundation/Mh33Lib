#include <iostream>
#include <iomanip> // put_time
#include "Util/MhUUID.hpp"

int main(int argc, char *argv[])
{
	MH33::RNG rngesus;
	MH33::UUID uuid(rngesus);
	std::cout << "UUID: " << uuid.toString(true) << std::endl;
	std::chrono::milliseconds millisecs;
	uint32_t rand1,rand2;
	uuid.toTimeAndRandom(millisecs,rand1,rand2);
	auto timePt = std::chrono::time_point<std::chrono::system_clock,std::chrono::milliseconds>(millisecs);
	auto in_time_t = std::chrono::system_clock::to_time_t(timePt);
	std::cout << "Time: " << std::put_time(std::localtime(&in_time_t), "%Y-%m-%d %X") << std::endl;
	std::cout << "Rand A: " << rand1 << std::endl;
	std::cout << "Rand B: " << rand2 << std::endl;
	return 0;
}

