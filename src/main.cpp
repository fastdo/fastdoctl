
#include "ctl_common.hpp"
#include "ctl_ControlCenterApp.hpp"
#include "ctl_api_handlers.hpp"
#include "ctl_web_handlers.hpp"

void StartupServer()
{
    ControlCenterApp app;
    // 设置处理器
    SET_API_HANDLER( app, get_os_info );
    SET_API_HANDLER( app, get_compiler_info );
    SET_API_HANDLER( app, get_libs_info );
    SET_API_HANDLER( app, get_envvars_info );
    SET_API_HANDLER( app, get_webserver_info );
    SET_API_HANDLER( app, get_fastdo_info );
    SET_API_HANDLER( app, get_package_info );

    app.run(nullptr);
}

int StartupMain( CommandLineVars const & cmdVars )
{
    //Mixed info;
    //Mixed info2;
    //ScanSoftwareInstalledInfo( "Visual Studio.* 2017", &info );
    //cout << info.myJson(true,"  ","\n") << endl;

    //CheckEnvVars(&info2);
    //cout << info2.myJson(true,"  ","\n") << endl;
    Mixed packInfo;
    CheckFastdoPackage(&packInfo);
    cout << packInfo.myJson(true,"  ","\n") << endl;

    RegisterVars(packInfo, nullptr);

    return 0;
}

int main( int argc, char const ** argv, char const ** envp )
{
    // 初始化一些库和设置
    #if defined(__GNUC__) && !defined(WIN32) // on linux
    winux::Locale::Set("zh_CN.UTF-8");
    #else

    #endif

    winux::Locale __loc__;
    eiengd::GdInit __gdInit__;
    eiennet::SocketLib __sockInit__;

    #if defined(OS_WIN)
    ComInit comInit;
    #endif

    CommandLineVars cmdVars( argc, argv, "", "", "server" );

    if ( cmdVars.hasFlag("server") )
    {
        // 启动Web服务器
        StartupServer();
        return 0;
    }

    return StartupMain(cmdVars);
}
