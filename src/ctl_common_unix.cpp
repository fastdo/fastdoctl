
#include "ctl_common.hpp"

#include <regex>

String GetOsVersion()
{
    return "Linux";
}

bool CheckCompilerInfo( String const & strRegexSoftwareName, Mixed * compilerInfo )
{
    compilerInfo->createCollection();

    return false;
}

bool CheckThirdpartiesLibs( std::initializer_list<String> libs, Mixed * libsInfo )
{
    libsInfo->createCollection();

    return false;
}

// 系统环境变量 HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Control\Session Manager\Environment
// 用户环境变量 HKEY_CURRENT_USER\Environment
bool CheckEnvVars( Mixed * envvarsInfo )
{
    envvarsInfo->createCollection();

    return false;
}

bool ModifyEcpConfig( Mixed const & configs )
{

    return false;
}

bool CheckWebServerConfig( Mixed * configInfo )
{
    configInfo->createCollection();

    return false;
}

bool ModifyWebServerConfig( Mixed const & configs )
{
    return false;
}

