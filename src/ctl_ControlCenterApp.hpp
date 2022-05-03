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

// 注册API响应宏
#define SET_API_HANDLER(app, name) (app).setApiHandler( #name, API_##name )

class ControlCenterApp : public HttpApp
{
public:
    ControlCenterApp();

    void setApiHandler( String const & apiName, CrossRouteHandlerFunction handler );

    /** \brief 外部定义的数据 */
    AppServerExternalData _httpExternalData;
    /** \brief HttpApp私有数据 */
    struct HttpAppPrivateData
    {
        winux::String exeFile;
        winux::String exeDirPath;
        winux::String exeTitle;
    } _privateData;
private:
    // api处理器
    map< String, HttpApp::CrossRouteHandlerFunction > _apiHandlers;

};
