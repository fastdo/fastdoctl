
#include "ctl_common.hpp"
#include "ctl_ControlCenterApp.hpp"
#include "ctl_api_handlers.hpp"

#if defined(OS_WIN)
#include <comdef.h>
#import "ahadmin.tlb"
#endif

bool API_get_os_version( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i )
{
    RSP << GetOsVersion();

    return false;
}

bool API_check_compiler( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i )
{


    return false;
}
