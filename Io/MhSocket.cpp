#include "MhSocket.hpp"
#if defined(_WIN32)
#include "private/MhSockeWin32.hpp"
#elif defined(__unix__)
#include "private/MhSocketUnix.hpp"
#endif

namespace MH33 {
Socket::Socket()
{

}
}
