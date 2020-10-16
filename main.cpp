#include <iostream>
#include "Util/MhUUID.hpp"

int main(int argc, char *argv[])
{
	MH33::UUID uuid("123e4567-e89b-12d3-a456-426614174000");
	std::cout << uuid.toString(true) << std::endl;
	return 0;
}

