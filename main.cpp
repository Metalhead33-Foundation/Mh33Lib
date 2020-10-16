#include <iostream>
#include "Media/Image/MhDDS.hpp"
#include "Io/MhFile.hpp"

int main(int argc, char *argv[])
{
	MH33::Io::File fio("/tmp/FrederickGilbertOduber.dds",MH33::Io::Mode::READ);
	MH33::GFX::DecodeTarget target;
	MH33::GFX::DDS::decode(fio,target);
	int mipmapNum = 0;
	for(const auto& it : target.frames) {
		std::cout << "Mipmap " << mipmapNum << "\n-Width: " << it.width << "\n-Height: " << it.height << std::endl;
		++mipmapNum;
	}
	return 0;
}

