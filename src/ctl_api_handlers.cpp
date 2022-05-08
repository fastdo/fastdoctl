
#include "ctl_common.hpp"
#include "ctl_ControlCenterApp.hpp"
#include "ctl_api_handlers.hpp"

#if defined(OS_WIN)
#include <comdef.h>
#import "ahadmin.tlb"
#endif

bool API_get_os_info( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i )
{
    Mixed result;
    result.createCollection();
    result["os"] = GetOsVersion();
    RSP << result.myJson( false, "    ", "\n" );
    return false;
}

bool API_get_compiler_info( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i )
{
    Mixed result;
    CheckCompilerInfo( "Visual Studio( .*)? 2017", &result );
    RSP << result.myJson( false, "    ", "\n" );
    return false;
}

bool API_get_libs_info( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i )
{
    Mixed result;
    CheckThirdpartiesLibs( { "fcgi", "mysql", "pthread", "sqlite3secure" }, &result );
    RSP << result.myJson( false, "    ", "\n" );
    return false;
}

bool API_get_envvars_info( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i )
{
    Mixed result;
    CheckEnvVars(&result);
    RSP << result.myJson( false, "    ", "\n" );
    return false;
}
