#include "MhMNG.hpp"
#include <libmng.h>
#include <memory>
mng_bool mh33_mng_openstream(mng_handle hHandle);
mng_bool mh33_mng_closestream(mng_handle hHandle);
mng_bool mh33_mng_readdata(mng_handle hHandle, mng_ptr pBuf, mng_uint32  iBuflen, mng_uint32p pRead);
mng_bool mh33_mng_writedata(mng_handle hHandle, mng_ptr pBuf, mng_uint32  iBuflen, mng_uint32p pRead);
namespace MH33 {
namespace GFX {

namespace MNG
{

bool decode(IoDevice &iodev)
{
	//std::unique_ptr<mng_data_struct,decltype (&mng_cleanup)> handle(mng_initialize(&iodev,nullptr,nullptr,nullptr),mng_cleanup);
	mng_handle handle = mng_initialize(&iodev,nullptr,nullptr,nullptr);
	if(!handle) return false;
	mng_setcb_openstream(handle,mh33_mng_openstream);
	mng_setcb_closestream(handle,mh33_mng_closestream);
	mng_setcb_readdata(handle,mh33_mng_readdata);
	//mng_setcb_writedata(handle.get(),mh33_mng_writedata);
	return true;
}

}

}
}
mng_bool mh33_mng_openstream(mng_handle hHandle) {
	auto devptr = reinterpret_cast<MH33::IoDevice*>(mng_get_userdata(hHandle));
	if(!devptr) return false;
	else return devptr->seek(MH33::SeekOrigin::SET,0);
}
mng_bool mh33_mng_closestream(mng_handle hHandle) {
	(void)hHandle;
	return MNG_TRUE;
}
mng_bool mh33_mng_readdata(mng_handle hHandle, mng_ptr pBuf, mng_uint32  iBuflen, mng_uint32p pRead) {
	auto devptr = reinterpret_cast<MH33::IoDevice*>(mng_get_userdata(hHandle));
	if(!devptr) return MNG_FALSE;
	else *pRead = devptr->read(pBuf,iBuflen);
	return MNG_TRUE;
}
mng_bool mh33_mng_writedata(mng_handle hHandle, mng_ptr pBuf, mng_uint32  iBuflen, mng_uint32p pRead) {
	auto devptr = reinterpret_cast<MH33::IoDevice*>(mng_get_userdata(hHandle));
	if(!devptr) return MNG_FALSE;
	else *pRead = devptr->write(pBuf,iBuflen);
	return MNG_TRUE;
}
/*
typedef mng_bool   (MNG_DECL *mng_openstream)    (mng_handle  hHandle);
typedef mng_bool   (MNG_DECL *mng_closestream)   (mng_handle  hHandle);
typedef mng_bool   (MNG_DECL *mng_readdata)      (mng_handle  hHandle,
												  mng_ptr     pBuf,
												  mng_uint32  iBuflen,
												  mng_uint32p pRead);
typedef mng_bool   (MNG_DECL *mng_writedata)     (mng_handle  hHandle,
												  mng_ptr     pBuf,
												  mng_uint32  iBuflen,
												  mng_uint32p pWritten);
*/
