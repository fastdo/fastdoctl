
#include "ctl_common.hpp"
#include "ctl_ControlCenterApp.hpp"
#include "ctl_api_handlers.hpp"

#if defined(OS_WIN)
#include <comdef.h>
#import "ahadmin.tlb"
#endif

bool API_get_os_version( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i )
{
    Mixed result;
    result.createCollection();
    result["os"] = GetOsVersion();

    RSP << result.myJson( false, "    ", "\n" );
    return false;
}

bool API_check_compiler(SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i)
{
    String compilerName, installPath;
    Mixed result;
    result.createCollection();

    if ( CheckCompiler( &compilerName, &installPath ) )
    {
        result["compiler"] = compilerName;
        result["installPath"] = installPath;

        String vsToolsBat64 = CombinePath( installPath, "VC\\Auxiliary\\Build\\vcvars64.bat" );
        if ( DetectPath(vsToolsBat64) )
        {
            result["VSToolsBat64"] = vsToolsBat64;
        }
        String vsToolsBat32 = CombinePath( installPath, "VC\\Auxiliary\\Build\\vcvars32.bat" );
        if ( DetectPath(vsToolsBat32) )
        {
            result["VSToolsBat32"] = vsToolsBat32;
        }

    }

    RSP << result.myJson( false, "    ", "\n" );
    return false;
}
