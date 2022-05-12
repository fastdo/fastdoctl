
#include "ctl_common.hpp"

#include <regex>

#if defined(OS_WIN)
#include <comdef.h>
#import "ahadmin.tlb"
#endif

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
    String version;
    typedef void (WINAPI * PGNSI)(LPSYSTEM_INFO);
    typedef BOOL (WINAPI * PGPI)( DWORD, DWORD, DWORD, DWORD, PDWORD );
    OSVERSIONINFOEX osvi;
    SYSTEM_INFO si;
    PGNSI pGNSI;
    PGPI pGPI;
    BOOL bOsVersionInfoEx;
    DWORD dwType;

    ZeroMemory( &si, sizeof(SYSTEM_INFO) );
    ZeroMemory( &osvi, sizeof(OSVERSIONINFOEX) );

    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);

    if( !( bOsVersionInfoEx = GetVersionEx( (OSVERSIONINFO *)&osvi ) ) )
        return _T("");

    // Call GetNativeSystemInfo if supported or GetSystemInfo otherwise.
    pGNSI = (PGNSI)GetProcAddress( GetModuleHandle( _T("kernel32.dll") ), "GetNativeSystemInfo" );
    if( NULL != pGNSI )
        pGNSI(&si);
    else
        GetSystemInfo(&si);

    version += _T("Microsoft");

    if ( VER_PLATFORM_WIN32_NT == osvi.dwPlatformId && osvi.dwMajorVersion > 4 )
    {
        typedef void (__stdcall * PFN_RtlGetNtVersionNumbers)(DWORD*, DWORD*, DWORD*);
        DWORD dwMajor, dwMinor, dwBuildNumber;
        bool isHighVersion = false;
        PFN_RtlGetNtVersionNumbers pfnRtlGetNtVersionNumbers = (PFN_RtlGetNtVersionNumbers)GetProcAddress( GetModuleHandle( _T("ntdll.dll") ), "RtlGetNtVersionNumbers");
        if ( pfnRtlGetNtVersionNumbers )
        {
            pfnRtlGetNtVersionNumbers( &dwMajor, &dwMinor, &dwBuildNumber );

            osvi.dwMajorVersion = dwMajor;
            osvi.dwMinorVersion = dwMinor;
            osvi.dwBuildNumber = dwBuildNumber;
            isHighVersion = true;
        }

        // Test for the specific product.
        if ( osvi.dwMajorVersion == 10 )
        {
            if ( osvi.dwMinorVersion == 0 )
            {
                if ( osvi.wProductType == VER_NT_WORKSTATION )
                    version += _T(" Windows 10");
                else
                    version += _T(" Windows Server 2016");
            }
            goto OS_TYPE;
        }
        else if ( osvi.dwMajorVersion == 6 )
        {
            if ( osvi.dwMinorVersion == 0 )
            {
                if ( osvi.wProductType == VER_NT_WORKSTATION )
                    version += _T(" Windows Vista");
                else
                    version += _T(" Windows Server 2008");
            }
            else if ( osvi.dwMinorVersion == 1 )
            {
                if ( osvi.wProductType == VER_NT_WORKSTATION )
                    version += _T(" Windows 7");
                else
                    version += _T(" Windows Server 2008 R2");
            }
            else if ( osvi.dwMinorVersion == 2 )
            {
                if ( osvi.wProductType == VER_NT_WORKSTATION )
                    version += _T(" Windows 8");
                else
                    version += _T(" Windows Server 2012");
            }
            else if ( osvi.dwMinorVersion == 3 )
            {
                if ( osvi.wProductType == VER_NT_WORKSTATION )
                {
                    version += _T(" Windows 8.1");
                }
                else
                {
                    version += _T(" Windows Server 2012 R2");
                }
            }

        OS_TYPE:
            pGPI = (PGPI)GetProcAddress( GetModuleHandle( _T("kernel32.dll") ), "GetProductInfo" );
            pGPI( osvi.dwMajorVersion, osvi.dwMinorVersion, 0, 0, &dwType);

            switch( dwType )
            {
            case PRODUCT_ULTIMATE:
                version += _T(" Ultimate Edition");
                break;
            case PRODUCT_PROFESSIONAL:
                version += _T(" Professional");
                break;
            case PRODUCT_HOME_PREMIUM:
                version += _T(" Home Premium Edition");
                break;
            case PRODUCT_HOME_BASIC:
                version += _T(" Home Basic Edition");
                break;
            case PRODUCT_ENTERPRISE:
                version += _T(" Enterprise Edition");
                break;
            case PRODUCT_BUSINESS:
                version += _T(" Business Edition");
                break;
            case PRODUCT_STARTER:
                version += _T(" Starter Edition");
                break;
            case PRODUCT_CLUSTER_SERVER:
                version += _T(" Cluster Server Edition");
                break;
            case PRODUCT_DATACENTER_SERVER:
                version += _T(" Datacenter Edition");
                break;
            case PRODUCT_DATACENTER_SERVER_CORE:
                version += _T(" Datacenter Edition (core installation)");
                break;
            case PRODUCT_ENTERPRISE_SERVER:
                version += _T(" Enterprise Edition");
                break;
            case PRODUCT_ENTERPRISE_SERVER_CORE:
                version += _T(" Enterprise Edition (core installation)");
                break;
            case PRODUCT_ENTERPRISE_SERVER_IA64:
                version += _T(" Enterprise Edition for Itanium-based Systems");
                break;
            case PRODUCT_SMALLBUSINESS_SERVER:
                version += _T(" Small Business Server");
                break;
            case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
                version += _T(" Small Business Server Premium Edition");
                break;
            case PRODUCT_STANDARD_SERVER:
                version += _T(" Standard Edition");
                break;
            case PRODUCT_STANDARD_SERVER_CORE:
                version += _T(" Standard Edition (core installation)");
                break;
            case PRODUCT_WEB_SERVER:
                version += _T(" Web Server Edition");
                break;
            }

        }
        else if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2 )
        {
            if( GetSystemMetrics(SM_SERVERR2) )
                version += _T(" Windows Server 2003 R2");
            else if ( osvi.wSuiteMask & VER_SUITE_STORAGE_SERVER )
                version += _T(" Windows Storage Server 2003");
            else if ( osvi.wSuiteMask & VER_SUITE_WH_SERVER )
                version += _T(" Windows Home Server");
            else if( osvi.wProductType == VER_NT_WORKSTATION && si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 )
                version += _T(" Windows XP Professional x64 Edition");
            else
                version += _T(" Windows Server 2003");

            // Test for the server type.
            if ( osvi.wProductType != VER_NT_WORKSTATION )  
            {
                if ( si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64 )
                {
                    if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                        version += _T(" Datacenter Edition for Itanium-based Systems");
                    else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                        version += _T(" Enterprise Edition for Itanium-based Systems");
                }
                else if ( si.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64 )
                {
                    if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                        version += _T(" Datacenter x64 Edition");
                    else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                        version += _T(" Enterprise x64 Edition");
                    else
                        version += _T(" Standard x64 Edition");
                }
                else  
                {  
                    if ( osvi.wSuiteMask & VER_SUITE_COMPUTE_SERVER )
                        version += _T(" Compute Cluster Edition");
                    else if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                        version += _T(" Datacenter Edition");
                    else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                        version += _T(" Enterprise Edition");
                    else if ( osvi.wSuiteMask & VER_SUITE_BLADE )
                        version += _T(" Web Edition");
                    else
                        version += _T(" Standard Edition");
                }
            }
        }
        else if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1 )
        {
            version += _T(" Windows XP");
            if( osvi.wSuiteMask & VER_SUITE_PERSONAL )
                version += _T(" Home Edition");
            else
                version += _T(" Professional");
        }
        else if ( osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0 )
        {
            version += _T(" Windows 2000");
            if ( osvi.wProductType == VER_NT_WORKSTATION )
            {
                version += _T(" Professional");
            }
            else
            {
                if( osvi.wSuiteMask & VER_SUITE_DATACENTER )
                    version += _T(" Datacenter Server");
                else if( osvi.wSuiteMask & VER_SUITE_ENTERPRISE )
                    version += _T(" Advanced Server");
                else
                    version += _T(" Server");
            }
        }

        // Include service pack (if any) and build number.  
        if( _tcslen(osvi.szCSDVersion) > 0 )  
        {  
            version += _T(" ");
            version += osvi.szCSDVersion;
        }

        version += Format( TEXT(" (build %u)"), isHighVersion ? osvi.dwBuildNumber & 0xFFFF : osvi.dwBuildNumber );

        if ( osvi.dwMajorVersion >= 6 )
        {
            if ( si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64 )
                version += TEXT(" 64-bit");
            else if (si.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_INTEL )
                version += _T(" 32-bit");
        }
    }
    else
    {
        version += _T(" Windows 9x or lower");
    }

    return version;
}

// 打开键句柄
HKEY RegistryOpenKey( LPCSTR keyName, BOOL wantWrite )
{
    HKEY baseKeyHandle = NULL, keyHandle = NULL;
    LPCSTR str = strchr( keyName, '\\' );
    if ( !str ) str = keyName + strlen(keyName); //只是根键的情况.
    if ( !_strnicmp( keyName, "HKEY_CLASSES_ROOT", str - keyName ) || !_strnicmp( keyName, "HKCR", str - keyName ) )
        baseKeyHandle = HKEY_CLASSES_ROOT;
    else if ( !_strnicmp( keyName, "HKEY_CURRENT_CONFIG", str - keyName ) || !_strnicmp( keyName, "HKCC", str - keyName ) )
        baseKeyHandle = HKEY_CURRENT_CONFIG;
    else if ( !_strnicmp( keyName, "HKEY_CURRENT_USER", str - keyName ) || !_strnicmp( keyName, "HKCU", str - keyName ) )
        baseKeyHandle = HKEY_CURRENT_USER;
    else if ( !_strnicmp( keyName, "HKEY_LOCAL_MACHINE", str - keyName ) || !_strnicmp( keyName, "HKLM", str - keyName ) )
        baseKeyHandle = HKEY_LOCAL_MACHINE;
    else if ( !_strnicmp( keyName, "HKEY_USERS", str - keyName ) || !_strnicmp( keyName, "HKU", str - keyName ) )
        baseKeyHandle = HKEY_USERS;
    else
    {
        return NULL;
    }
    if ( !*str )
    {
        return baseKeyHandle;
    }
    str++;	//跳过'\\'
    if ( baseKeyHandle )
    {
        if ( wantWrite )  //以写方式,若以存在,则打开,不存在则创建.
            RegCreateKey( baseKeyHandle, str, &keyHandle );
        else
            RegOpenKey( baseKeyHandle, str, &keyHandle );
    }
    return keyHandle;
}

// 关闭键句柄
int RegistryCloseKey( HKEY keyHandle )
{
    if (
        keyHandle == HKEY_CLASSES_ROOT ||
        keyHandle == HKEY_CURRENT_USER ||
        keyHandle == HKEY_LOCAL_MACHINE ||
        keyHandle == HKEY_USERS ||
        keyHandle == HKEY_CURRENT_CONFIG
    )
    {
        return 0;
    }
    return RegCloseKey(keyHandle);
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
        SimpleHandle<HKEY> key( RegistryOpenKey( strKey.c_str(), TRUE ), 0, RegistryCloseKey );

        CHAR szSubKey[256] = { 0 };
        for ( DWORD i = 0; RegEnumKey( key.get(), i, szSubKey, sizeof(szSubKey) ) != ERROR_NO_MORE_ITEMS; ++i )
        {
            CHAR szOneValue[256] = { 0 };
            DWORD cb;
            DWORD dwType;

            String strSubKey = strKey + "\\" + szSubKey;
            SimpleHandle<HKEY> subKey( RegistryOpenKey( strSubKey.c_str(), TRUE ), 0, RegistryCloseKey );

            dwType = REG_SZ;
            cb = sizeof(szOneValue);
            memset( szOneValue, 0, cb );
            RegQueryValueExA(subKey.get(), "DisplayName", NULL, &dwType, (LPBYTE)szOneValue, &cb);
            AnsiString strDisplayName = szOneValue;

            if ( strDisplayName.length() > 0 )
            {
                std::regex re{ strRegexSoftwareName, regex::ECMAScript };

                if ( regex_match( strDisplayName, re ) )
                {
                    dwType = REG_SZ;
                    cb = sizeof(szOneValue);
                    memset( szOneValue, 0, cb );
                    RegQueryValueExA( subKey.get(), "InstallLocation", NULL, &dwType, (LPBYTE)szOneValue, &cb);
                    Mixed & mxInstallPath = (*installedColl)[strDisplayName];

                    mxInstallPath = szOneValue;
                    if ( mxInstallPath._pStr->empty() )
                    {
                        dwType = REG_SZ;
                        cb = sizeof(szOneValue);
                        memset( szOneValue, 0, cb );
                        RegQueryValueExA( subKey.get(), "DisplayIcon", NULL, &dwType, (LPBYTE)szOneValue, &cb);

                        mxInstallPath = FilePath(szOneValue);
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
        int n = installedColl.getCount();
        for ( int i = 0; i < n; ++i )
        {
            auto & pr = installedColl.getPair(i);
            *compilerName = pr.first;
            *installPath = pr.second;
            return true;
        }
    }
    return false;
}

bool CheckCompilerInfo( String const & strRegexSoftwareName, Mixed * compilerInfo )
{
    compilerInfo->createCollection();

    String compilerName, installPath;

    if ( ScanCompilerInstallPath( strRegexSoftwareName, &compilerName, &installPath ) )
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

bool CheckThirdpartiesLibs( std::initializer_list<String> libs, Mixed * libsInfo )
{
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
                r = false;
            }
        }
    }

    return r;
}

// 系统环境变量 HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment
// 用户环境变量 HKEY_CURRENT_USER\Environment
bool CheckEnvVars( Mixed * envvarsInfo )
{
    envvarsInfo->createCollection();
    String strKey = R"(HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment)";
    SimpleHandle<HKEY> key( RegistryOpenKey( strKey.c_str(), TRUE ), 0, RegistryCloseKey );
    CHAR szName[256] = { 0 };
    CHAR szValue[1024] = { 0 };
    DWORD dwNameLen = sizeof(szName);
    DWORD dwValueLen = sizeof(szValue);
    DWORD dwType = REG_NONE;
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
    for ( String const & var : targetVars )
    {
        (*envvarsInfo)["FASTDO_" + var] = Mixed();
    }
    for ( DWORD i = 0; RegEnumValue( key.get(), i, szName, &dwNameLen, NULL, &dwType, (LPBYTE)szValue, &dwValueLen ) != ERROR_NO_MORE_ITEMS; ++i )
    {
        match_results<String::const_iterator> mres;
        String strName = szName;
        if ( regex_match( strName, mres, re ) )
        {
            //cout << strName << ", type=" << dwType << ", " << mres[1] << endl;
            (*envvarsInfo)[strName] = szValue;
        }

        dwNameLen = sizeof(szName);
        dwValueLen = sizeof(szValue);
        dwType = REG_NONE;
    }
    bool r = true;
    for ( String const & var : targetVars )
    {
        if ( (*envvarsInfo)["FASTDO_" + var].isNull() )
        {
            r = false;
            break;
        }
    }
    return r;
}

bool ModifyEcpConfig( Mixed const & configs )
{
    return false;
}
