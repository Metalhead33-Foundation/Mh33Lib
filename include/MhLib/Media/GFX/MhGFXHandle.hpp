#ifndef MHTGFXHANDLE_HPP
#define MHTGFXHANDLE_HPP
#include <MhLib/Media/GFX/MhGFX.hpp>
#include <cstdint>

namespace MH33 {
namespace GFX {

union Handle {
	void* ptr;
	int ginteger;
	unsigned guintenger;
	int32_t gint32;
	uint32_t guint32;
	int64_t gint64;
	uint64_t guint64;
};

}
}
#endif // MHTGFXHANDLE_HPP
