#include "ctl_common.hpp"
#include "ctl_ControlCenterApp.hpp"
#include "ctl_api_handlers.hpp"

#include "fastdo.ver"

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

bool API_get_fastdo_info( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i )
{
    Mixed result;
    result.createCollection();
    result["path"] = GetCurrentFastdoPackage();
    result["version"] = FASTDO_VERSION_STRING;
    RSP << result.myJson( false, "    ", "\n" );
    return false;
}

bool API_get_package_info( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i )
{
    Mixed result;
    CheckFastdoPackage(&result);
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
    StringArray targetLbs;
    Mixed & libs = requestCtxPtr->get["libs"];
    if ( libs.isArray() )
    {
        libs.getArray(&targetLbs);
        cout << "LIBS: " << targetLbs << endl;
    }

    targetLbs.insert( targetLbs.begin(), { "fcgi", "mysql", "pthread", "sqlite3secure" } );

    Mixed result;
    CheckThirdpartiesLibs( targetLbs, &result );
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

bool API_get_webserver_info( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i )
{
    Mixed result;
    CheckWebServerConfig(&result);
    RSP << result.myJson( false, "    ", "\n" );
    return false;
}
