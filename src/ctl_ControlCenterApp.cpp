
#include "ctl_common.hpp"
#include "ctl_ControlCenterApp.hpp"
#include "ctl_web_handlers.hpp"

// 时区
static winux::String __strTimezone;

// class ControlApp -----------------------------------------------------------------------
ControlCenterApp::ControlCenterApp()
{
    _privateData.exeDirPath = winux::FilePath( winux::GetExecutablePath(), &_privateData.exeFile );
    _privateData.exeTitle = winux::FileTitle(_privateData.exeFile);

    // 载入配置文件 webx_httpserv.settings
    winux::ConfigureSettings settings;
    settings.set( "$ExeDirPath", _privateData.exeDirPath );
    settings.set( "$WorkDirPath", winux::RealPath("") );
    settings.load( winux::CombinePath( _privateData.exeDirPath, _privateData.exeTitle + ".settings" ) );
    // 输出配置信息
    winux::ColorOutputLine( winux::fgYellow, settings.val().myJson( true, "    ", "\n" ) );

    // Session 相关选项
    // sessions save path
    winux::String sessionsSavePath;
    //sessionsSavePath = settings.has("SessionsPath") ? settings.get("SessionsPath").toAnsi() : winux::CombinePath( _privateData.exeDirPath, "sessions" );
    sessionsSavePath = settings.execVal( "SessionsPath", winux::CombinePath( _privateData.exeDirPath, "sessions" ) ).toAnsi();

    // 确保路径存在
    winux::MakeDirExists(sessionsSavePath);
    // 文件式session服务,构造参数为一个session文件存储路径
    eienwebx::FileSessionServer sessServ(sessionsSavePath);

    _httpExternalData.serverPath = winux::CombinePath( _privateData.exeDirPath, _privateData.exeFile ); // httpserv路径
    _httpExternalData.pid = getpid(); // 进程ID
    _httpExternalData.fastdoVer =
        #include "fastdo.ver"
    ; // 版本号


    // 设置时区环境变量
    __strTimezone = "TZ=" + settings.execVal( "server.time_zone", "" ).toAnsi();
    putenv( &__strTimezone[0] );

    // 初始化App对象
    this->init( settings, &_httpExternalData );
    // 设置SessionServer
    this->setSessServ(&sessServ);

    // 注册web处理响应
    RegisterWebHandlers(*this);

}
