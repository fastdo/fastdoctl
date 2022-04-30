#include "winux.hpp"

#if defined(OS_WIN)
#include <comdef.h>
#import "ahadmin.tlb"

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

#include "appserv.hpp"
#include "eienwebx.hpp"
#include "eiengd.hpp"

using namespace std;
using namespace winux;
using namespace eiennet;
using namespace eienwebx;
using namespace eiengd;

#if defined(_MSC_VER) || defined(WIN32)
    #include <process.h>

    #define getpid _getpid
#else
    #include <sys/types.h>
    #include <sys/ipc.h>
    #include <sys/msg.h>
    #include <unistd.h>
#endif

#include <stdlib.h>
#include <string.h>
#include <signal.h>

// httpserv公开数据
AppServerExternalData __httpExternalData;
// 时区
winux::String __strTimezone;

/** \brief HttpApp私有数据 */
struct HttpAppPrivateData
{
    winux::String exeFile;
    winux::String exeDirPath;
    winux::String exeTitle;
};

void RegisterWebHandlers( eienwebx::HttpApp & app )
{
    app.crossRoute( "*", "/", [] ( winux::SharedPointer<HttpRequestCtx> requestCtxPtr, eienwebx::Response & RSP, winux::StringArray const & urlPathPartArr, size_t i ) -> bool {
        RSP.header["Access-Control-Allow-Origin"] = "*";
        return true;
    } );


}

int main()
{
    HttpAppPrivateData privateData;
    privateData.exeDirPath = winux::FilePath( winux::GetExecutablePath(), &privateData.exeFile );
    privateData.exeTitle = winux::FileTitle(privateData.exeFile);

    // 载入配置文件 webx_httpserv.settings
    winux::ConfigureSettings settings;
    settings.set( "$ExeDirPath", privateData.exeDirPath );
    settings.set( "$WorkDirPath", winux::RealPath("") );
    settings.load( winux::CombinePath( privateData.exeDirPath, privateData.exeTitle + ".settings" ) );
    // 输出配置信息
    winux::ColorOutputLine( winux::fgYellow, settings.val().myJson( true, "    ", "\n" ) );

    // Session 相关选项
    // sessions save path
    winux::String sessionsSavePath;
    sessionsSavePath = settings.has("SessionsPath") ? settings.get("SessionsPath").toAnsi() : winux::CombinePath( privateData.exeDirPath, "sessions" );
    // 确保路径存在
    winux::MakeDirExists(sessionsSavePath);
    // 文件式session服务,构造参数为一个session文件存储路径
    eienwebx::FileSessionServer sessServ(sessionsSavePath);

    __httpExternalData.serverPath = winux::CombinePath( privateData.exeDirPath, privateData.exeFile ); // httpserv路径
    __httpExternalData.pid = getpid(); // 进程ID
    __httpExternalData.fastdoVer =
        #include "fastdo.ver"
    ; // 版本号

    // 初始化一些库和设置

    // 设置时区环境变量
    __strTimezone = "TZ=" + settings.execVal( "server.time_zone", "" ).toAnsi();
    putenv( &__strTimezone[0] );

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

    eienwebx::HttpApp app{ settings, &__httpExternalData }; // 创建一个HttpApp对象
    app.setSessServ(&sessServ);

    RegisterWebHandlers(app);

    return app.run(nullptr);
}
