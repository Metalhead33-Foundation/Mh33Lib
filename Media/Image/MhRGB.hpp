#ifndef MHRGBCOLOUR_HPP
#define MHRGBCOLOUR_HPP

namespace MH33 {
namespace GFX {

template <typename ColourResolution> struct RGB {
	ColourResolution r,g,b;
};
template <typename ColourResolution> struct BGR {
	ColourResolution b,g,r;
};
template <typename ColourResolution> struct RGBA {
	ColourResolution r,g,b,a;
};
template <typename ColourResolution> struct BGRA {
	ColourResolution b,g,r,a;
};
template <typename ColourResolution> struct ARGB {
	ColourResolution a,r,g,b;
};

}
}
#endif // MHRGBCOLOUR_HPP
