#include <iostream>
#include <Media/Image/MhStandardColourFormat.hpp>

int main(int argc, char *argv[])
{
	MH33::GFX::RGB<uint8_t> a = { 122, 66, 20 };
	float b;
	MH33::GFX::colour_cast(a,b);
	std::cout << "R: " << b << std::endl;
	return 0;
}

