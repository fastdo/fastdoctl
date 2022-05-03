
#include "ctl_common.hpp"
#include "ctl_ControlCenterApp.hpp"
#include "ctl_api_handlers.hpp"
#include "ctl_web_handlers.hpp"

int main()
{
    // 初始化一些库和设置
    #if defined(__GNUC__) && !defined(WIN32) // on linux
    winux::SetLocale::Set("zh_CN.UTF-8");
    #else

    #endif

    winux::SetLocale __loc__;
    eiengd::GdInit __gdInit__;
    eiennet::SocketLib __sockInit__;
    #if defined(OS_WIN)
    ComInit comInit;
    #endif

    ControlCenterApp app;

    SET_API_HANDLER(app, get_os_version);

    return app.run(nullptr);
}
