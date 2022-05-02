#pragma once

#if defined(OS_WIN)
//#include <comdef.h>
//#import "ahadmin.tlb"

// COM库初始化
class ComInit
{
public:
    ComInit() : _hr(S_OK)
    {
        _hr = CoInitializeEx( NULL, COINIT_MULTITHREADED );
    }
    ~ComInit()
    {
        CoUninitialize();
    }
private:
    HRESULT _hr;

    DISABLE_OBJECT_COPY(ComInit)
};
#endif

class ControlCenterApp : public HttpApp
{
public:
    ControlCenterApp();

    AppServerExternalData _httpExternalData;
    /** \brief HttpApp私有数据 */
    struct HttpAppPrivateData
    {
        winux::String exeFile;
        winux::String exeDirPath;
        winux::String exeTitle;
    } _privateData;
private:

};
