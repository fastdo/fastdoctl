
#include "ctl_common.hpp"

SimpleHandle<char *> GetErrorStr( uint32 err )
{
    char * buf = NULL;
    DWORD dw = FormatMessageA(
        FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS | FORMAT_MESSAGE_ALLOCATE_BUFFER,
        NULL,
        err,
        0,
        (LPSTR)&buf,
        256,
        NULL
    );

    return SimpleHandle<char *>( buf, NULL, LocalFree );
}

String GetOsVersion()
{
    return StrTrim( GetExec("cmd /c ver") );
}
