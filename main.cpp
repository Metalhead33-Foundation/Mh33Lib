#include <iostream>
#include <Media/Image/MhStandardColourFormat.hpp>

int main(int argc, char *argv[])
{
	MH33::GFX::RGB<uint8_t> a = { 122, 66, 20 };
	MH33::GFX::RGB<uint8_t> b;
	MH33::GFX::colour_cast(a,b);
	std::cout << "R: " << reinterpret_cast<size_t>(&b) - reinterpret_cast<size_t>(&a) << std::endl;
	return 0;
}

