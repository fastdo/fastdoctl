
#include "ctl_common.hpp"

#include <regex>

String GetOsVersion()
{
    DirIterator dir("/etc/");
    regex re(".*-release");
    String releaseContent;
    while ( dir.next() )
    {
        if ( dir.isDir() ) continue;
        if ( !regex_match( dir.getName(), re ) ) continue;
        releaseContent += FileGetContents(dir.getFullPath());
    }

    String pattern = "PRETTY_NAME=";
    String prettyName = "\"Unix-like\"";
    size_t pos;
    if ( ( pos = releaseContent.find(pattern) ) != String::npos )
    {
        size_t pos1;
        if ( ( pos1 = releaseContent.find( "\n", pos + pattern.length() ) ) != String::npos )
        {
            prettyName = releaseContent.substr( pos + pattern.length(), pos1 - (pos + pattern.length()) );
        }
        else
        {
            prettyName = releaseContent.substr( pos + pattern.length() );
        }
    }

    return Json(prettyName);
}

String GetFastdoPackage()
{
    return NormalizePath( FilePath( GetExecutablePath() ) + DirSep + ".." );
}

bool CheckCompilerInfo( String const & strRegexSoftwareName, Mixed * compilerInfo )
{
    compilerInfo->createCollection();
    int i = 0;
    String gppVersion;
    StrGetLine( &gppVersion, GetExec("g++ --version"), &i );
    //cout << gccVersion << endl;
    String gppInstallPath;
    i = 0;
    StrGetLine( &gppInstallPath, GetExec("which g++"), &i );
    //cout << gccInstallPath << endl;
    compilerInfo->addPair()
        ( "compiler", gppVersion )
        ( "installPath", gppInstallPath )
        ( "script", "" )
    ;

    return gppInstallPath.find("no g++") == String::npos;
}

bool CheckThirdpartiesLibs( std::initializer_list<String> libs, Mixed * libsInfo )
{
    libsInfo->createCollection();

    return false;
}

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

