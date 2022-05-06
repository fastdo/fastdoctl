
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

bool API_check_compiler(SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i)
{
    //RSP.setMimeType("text/plain");
    //RSP.setCharset("utf-8");
    //RSP.header["Content-Type"] = "text/html; charset=utf-8";

    /*Mixed installed;
    if ( ScanSoftwareInstalledInfo( "Visual Studio( .*)? 2017", &installed ) )
    {
        RSP << "<pre>" << installed.myJson(true, "    ", "\n") << "</pre>" << endl;
    }*/

    String compilerName, installedPath;

    if ( CheckCompiler( &compilerName, &installedPath ) )
    {
        RSP << compilerName << " = " << installedPath;
    }

    /*if ( ScanSoftwareInstalledInfo( ".*", &installed ) )
    {
        RSP << "<pre>" << installed.myJson(true, "    ", "\n") << "</pre>" << endl;
    }
    //*/

    return false;
}
