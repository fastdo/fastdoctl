#include "ctl_common.hpp"
#include "ctl_ControlCenterApp.hpp"
#include "ctl_web_handlers.hpp"

#include "fastdo.ver"

// 时区
static winux::String __strTimezone;

// class ControlApp -----------------------------------------------------------------------
ControlCenterApp::ControlCenterApp()
{
    _privateData.exeDirPath = winux::FilePath( winux::GetExecutablePath(), &_privateData.exeFile );
    _privateData.exeTitle = winux::FileTitle(_privateData.exeFile);

    // 载入配置文件 fastdoctl.settings
    winux::ConfigureSettings settings;
    settings.set( "$ExeDirPath", _privateData.exeDirPath );
    settings.set( "$WorkDirPath", winux::RealPath("") );
    winux::String settingsPath = winux::CombinePath( settings.get("$WorkDirPath"), _privateData.exeTitle + ".settings" );
    // 当前目录下的*.settings文件不存在，就去加载exe目录下的文件
    if ( !DetectPath(settingsPath) )
    {
        settingsPath = winux::CombinePath( settings.get("$ExeDirPath"), _privateData.exeTitle + ".settings" );
    }
    settings.load(settingsPath);
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
    _httpExternalData.fastdoVer = FASTDO_VERSION_STRING; // 版本号


    // 设置时区环境变量
    __strTimezone = "TZ=" + settings.execVal( "server.time_zone", "" ).toAnsi();
    putenv( &__strTimezone[0] );

    // 初始化App对象
    this->init( settings, &_httpExternalData );
    // 设置SessionServer
    this->setSessServ(&sessServ);

    // 注册处理响应
    this->crossRoute( "*", "/", [] ( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i ) -> bool {
        RSP.header["Access-Control-Allow-Origin"] = "*";
        return true;
    } );

    // 注册API处理响应
    this->crossRoute( "*", "/api", [this] ( SharedPointer<HttpRequestCtx> requestCtxPtr, Response & RSP, StringArray & urlPathPartArr, size_t i ) -> bool {
        ControlCenterApp * ccApp = static_cast<ControlCenterApp *>(requestCtxPtr->app);
        String apiName = StrJoinEx( "/", urlPathPartArr, (int)i + 1 );
        cout << Mixed(apiName).myJson() << endl;
        bool r;
        if ( isset( _apiHandlers, apiName ) )
        {
            r = _apiHandlers[apiName]( requestCtxPtr, RSP, urlPathPartArr, i );
        }
        else
        {
            String modFullPath = NormalizePath(ccApp->_privateData.exeDirPath + "/fastdoctl_mods/api" + ( apiName.empty() ? ".do" : "/" + apiName + ".do" ) );
            cout << modFullPath << endl;
            int rc = 0;
            ccApp->execWebMain( modFullPath, &RSP, ccApp->getRunParam(), &rc );
            cout << "rc=" << rc << endl;
            //cout << ccApp->_httpExternalData.serverPath << endl;
            r = false;
        }
        return r;
    } );

}

void ControlCenterApp::setApiHandler( String const & apiName, CrossRouteHandlerFunction handler )
{
    _apiHandlers[apiName] = handler;
}
