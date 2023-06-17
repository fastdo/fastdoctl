﻿
#include "ctl_common.hpp"
#include "winplus.hpp"
using namespace winplus;

#include <regex>

#include <comdef.h>
#import "ahadmin.tlb"


// Windows错误代码转错误串
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
    return winplus::GetOsVersion();
}

bool ScanSoftwareInstalledInfo( String const & strRegexSoftwareName, Mixed * installedColl )
{
    StringArray keyPaths = {
        R"(HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall)",
        R"(HKEY_LOCAL_MACHINE\SOFTWARE\WOW6432Node\Microsoft\Windows\CurrentVersion\Uninstall)",
        R"(HKEY_CURRENT_USER\SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall)"
    };

    installedColl->createCollection();

    bool r = false;
    for ( String & strKey : keyPaths )
    {
        Registry key(strKey);
        String strSubKey;
        while ( key.enumKeys(&strSubKey) )
        {
            Registry subKey( key.key(), strSubKey );
            AnsiString strDisplayName = subKey.getValue("DisplayName");
            if ( strDisplayName.length() > 0 )
            {
                std::regex re{ strRegexSoftwareName, regex::ECMAScript };
                if ( regex_match( strDisplayName, re ) )
                {
                    Mixed & mxInstallPath = (*installedColl)[strDisplayName];
                    mxInstallPath = subKey.getValue( "InstallLocation", "" );
                    if ( mxInstallPath._pStr->empty() )
                    {
                        mxInstallPath = FilePath( subKey.getValue("DisplayIcon") );
                        if ( mxInstallPath._pStr->empty() )
                        {
                            installedColl->del(strDisplayName);
                        }
                    }
                    r = true;
                }
            }
        }
    }

    return r;
}

bool ScanCompilerInstallPath( String const & strRegexSoftwareName, String * compilerName, String * installPath )
{
    Mixed installedColl;
    if ( ScanSoftwareInstalledInfo( strRegexSoftwareName, &installedColl ) )
    {
        size_t n = installedColl.getCount();
        for ( size_t i = 0; i < n; ++i )
        {
            auto & pr = installedColl.getPair(i);
            *compilerName = pr.first;
            *installPath = pr.second;
            return true;
        }
    }
    return false;
}

String GetCurrentFastdoPackage()
{
    return NormalizePath( FilePath( GetExecutablePath() ) + DirSep + ".." );
}

bool CheckFastdoPackage( Mixed * packInfo )
{
    packInfo->createCollection();
    String packPath = GetCurrentFastdoPackage();
    String basePath = FilePath(packPath);
    String includePath = CombinePath( basePath, "include" );

    (*packInfo)["base"] = Mixed();
    if ( DetectPath(basePath) ) (*packInfo)["base"] = basePath;
    (*packInfo)["include"] = Mixed();
    if ( DetectPath(includePath) ) (*packInfo)["include"] = includePath;

    Mixed & arch = (*packInfo)["arch"].createCollection();

    StringArray archDirs = { "x64-Debug", "x64-Release", "x86-Debug", "x86-Release" };
    for ( auto & archDir : archDirs )
    {
        String strArch = CollateIdentifierToString( archDir, "", wordAllUpper ).substr( 0, 4 );
        arch[strArch] = Mixed();
        if ( DetectPath( CombinePath( basePath, archDir ) ) )
        {
            arch[strArch] = CombinePath( basePath, archDir );
        }
    }

    return false;
}

bool CheckCompilerInfo( String const & strRegexSoftwareName, Mixed * compilerInfo )
{
    compilerInfo->createCollection();

    String compilerName, installPath;

    bool r = ScanCompilerInstallPath( strRegexSoftwareName, &compilerName, &installPath );
    (*compilerInfo)["check"] = r;

    if ( r )
    {
        (*compilerInfo)["compiler"] = compilerName;
        (*compilerInfo)["installPath"] = installPath;

        String vsToolsBat64 = CombinePath( installPath, "VC\\Auxiliary\\Build\\vcvars64.bat" );
        if ( DetectPath(vsToolsBat64) )
        {
            (*compilerInfo)["VSToolsBat64"] = vsToolsBat64;
        }
        String vsToolsBat32 = CombinePath( installPath, "VC\\Auxiliary\\Build\\vcvars32.bat" );
        if ( DetectPath(vsToolsBat32) )
        {
            (*compilerInfo)["VSToolsBat32"] = vsToolsBat32;
        }

        return true;
    }

    return false;
}

bool CheckThirdpartiesLibs( StringArray const & libs, Mixed * libsAllInfo )
{
    libsAllInfo->createCollection();
    Mixed * libsInfo = &(*libsAllInfo)["libs"];
    libsInfo->createCollection();
    bool r = true;
    String exePath = FilePath( GetExecutablePath() );
    String rootPath = PathWithSep( NormalizePath( CombinePath( exePath, ".." ) ) );
    for ( String const & lib : libs )
    {
        if ( lib == "fcgi" )
        {
            String libPath = CombinePath( exePath, "libfcgi.dll" );
            if ( DetectPath(libPath) )
            {
                (*libsInfo)[lib] = StrSubtractA( libPath, rootPath );
            }
            else
            {
                (*libsInfo)[lib] = Mixed();
                r = false;
            }
        }
        else if ( lib == "mysql" )
        {
            String libPath = CombinePath( exePath, "libmysql.dll" );
            if ( DetectPath(libPath) )
            {
                (*libsInfo)[lib] = StrSubtractA( libPath, rootPath );
            }
            else
            {
                (*libsInfo)[lib] = Mixed();
                r = false;
            }
        }
        else if ( lib == "pthread" )
        {
            String libPath = CombinePath( exePath, "pthreadVC2.dll" );
            if ( DetectPath(libPath) )
            {
                (*libsInfo)[lib] = StrSubtractA( libPath, rootPath );
            }
            else
            {
                (*libsInfo)[lib] = Mixed();
                r = false;
            }
        }
        else
        {
            String libPath = CombinePath( exePath, lib + ".dll" );
            if ( DetectPath(libPath) )
            {
                (*libsInfo)[lib] = StrSubtractA( libPath, rootPath );
            }
            else
            {
                (*libsInfo)[lib] = Mixed();
                r = false;
            }
        }
    }
    (*libsAllInfo)["check"] = r;
    return r;
}

// 系统环境变量 HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment
// 用户环境变量 HKEY_CURRENT_USER\Environment
// 存在FASTDO_BASE, FASTDO_INCLUDE, 和任意一对FASTDO_X***_BIN, FASTDO_X***_LIB就算检测OK
bool CheckEnvVars( Mixed * info )
{
    String strKey = R"(HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment)";
    Registry key(strKey);
    regex re( "FASTDO_(.+)", regex::ECMAScript );
    StringArray targetVars = {
        "BASE",
        "INCLUDE",
        "X64D_BIN",
        "X64D_LIB",
        "X64R_BIN",
        "X64R_LIB",
        "X86D_BIN",
        "X86D_LIB",
        "X86R_BIN",
        "X86R_LIB"
    };
    info->createCollection();
    Mixed & envvars = (*info)["envvars"].createCollection();
    // 初始设为Mixed(MT_NULL)
    for ( String const & var : targetVars )
    {
        envvars["FASTDO_" + var] = Mixed();
    }

    // 枚举目标环境变量
    String strName;
    Mixed value;
    while ( key.enumValues( &strName, &value ) )
    {
        match_results<String::const_iterator> mres;
        if ( regex_match( strName, mres, re ) )
        {
            envvars[strName] = Registry::Value(value);
        }
    }

    // 检测是否OK
    bool baseOk = false;
    bool includeOk = false;
    bool archOk = false;

    baseOk = envvars["FASTDO_BASE"].isString();
    includeOk = envvars["FASTDO_INCLUDE"].isString();

    Mixed & archInfo = (*info)["arch"].createCollection();
    StringArray archs = { "X64D", "X64R", "X86D", "X86R" };
    for ( auto & arch: archs )
    {
        archInfo[arch] = envvars["FASTDO_" + String(arch) + "_BIN"].isString() && envvars["FASTDO_" + String(arch) + "_LIB"].isString();
        if ( !archOk ) archOk = archInfo[arch];
    }

    return (*info)["check"] = baseOk && includeOk && archOk;
}

bool ModifyEcpConfig( Mixed const & configs )
{
    String exePath = FilePath( GetExecutablePath() );
    String ecpConfigPath = CombinePath( exePath, "ecp.conf" );
    String configContent = FileGetContents(ecpConfigPath);
    size_t offset = 0;

    size_t n = configs.getCount();
    for ( size_t i = 0; i < n; ++i )
    {
        auto const & pr = configs.getPair(i);
        size_t pos = configContent.find( "\n" + *pr.first._pStr, offset );
        if ( pos != String::npos )
        {
            pos++;
            size_t startPos = pos;
            while ( pos < configContent.length() && configContent[pos] != '\n' )
            {
                pos++;
            }
            size_t endPos = pos;
            String newConfigContent;
            newConfigContent = configContent.substr( 0, startPos );
            newConfigContent += *pr.first._pStr + "=" + *pr.second._pStr;
            newConfigContent += configContent.substr(endPos);
            configContent = newConfigContent;
        }
    }
    bool r = FilePutContents( ecpConfigPath, configContent );
    return r;
}

bool CheckWebServerConfig( Mixed * configInfo )
{
    configInfo->createCollection();

    using namespace AppHostAdminLibrary;
    try
    {
        IAppHostWritableAdminManagerPtr adminManager;

        adminManager.CreateInstance( __uuidof(AppHostWritableAdminManager), NULL, CLSCTX_INPROC_SERVER );

        //printf("IAppHostWritableAdminManager ok\n");

        IAppHostElementPtr handlersSection;
        handlersSection = adminManager->GetAdminSection( L"system.webServer/handlers", L"MACHINE/WEBROOT/APPHOST/Default Web Site" );

        IAppHostElementCollectionPtr handlersCollection = handlersSection->Collection;
        DWORD handlersCount = handlersCollection->Count;
        cout << handlersCount << endl;

        IAppHostPropertyCollectionPtr propertiesCollection = handlersSection->Properties;
        DWORD nProperties = propertiesCollection->Count;

        for ( DWORD i = 0; i < nProperties; ++i )
        {
            IAppHostPropertyPtr prop = propertiesCollection->Item[i];
            cout << prop->Name << " = ";
            cout << prop->StringValue << endl;
        }

        Mixed & handlersArr = (*configInfo)["handlers"].createArray();

        for ( DWORD i = 0; i < handlersCount; i++ )
        {

            IAppHostElementPtr handlerElem = handlersCollection->Item[i];
            //cout << i << ", " << handlerElem->Name << " -----------------------------------------------------------------\n";

            //IAppHostPropertyPtr nameProp = handlerElem->GetPropertyByName(L"name");
            //cout << nameProp->Name << ": " << nameProp->StringValue << endl;

            IAppHostPropertyCollectionPtr props = handlerElem->Properties;

            Mixed handlerInfo;
            handlerInfo.createCollection();
            bool isFastDoHandler = true;

            if ( props )
            {
                DWORD propCount = props->Count;
                for ( DWORD j = 0; j < propCount; j++ )
                {
                    IAppHostPropertyPtr prop = props->Item[j];

                    String propName = prop->Name.operator const char *();

                    regex reName{".*FastDo.*"};
                    if ( propName == "name" && !regex_match( prop->StringValue.operator const char *(), reName ) )
                    {
                        isFastDoHandler = false;
                    }

                    Mixed & hi = handlerInfo[propName];
                    hi.createCollection();

                    hi["vt"] = prop->Value.vt;

                    switch ( prop->Value.vt )
                    {
                    case VT_BSTR:
                        hi["value"] = prop->StringValue.operator const char *();
                        break;
                    case VT_BOOL:
                        hi["value"] = prop->Value.boolVal == VARIANT_TRUE ? true : false;
                        break;
                    case VT_UI4:
                        hi["value"] = prop->Value.uintVal;
                        break;
                    case VT_I4:
                    default:
                        hi["value"] = prop->Value.intVal;
                        break;
                    }
                }
            }

            if ( isFastDoHandler )
                handlersArr.add(handlerInfo);
        }

        //hr = ListSiteInfo( pSitesCollection.GetInterfacePtr() );
    }
    catch ( _com_error const & e )
    {
        cout << e.Description() << endl;
    }

    return false;
}

bool ModifyWebServerConfig( Mixed const & configs )
{
    return false;
}

