﻿#pragma once

#include "winux.hpp"
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
    #include <tchar.h>

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

// 获取操作系统版本串
String GetOsVersion();

// 获取当前支持fastdoctl运行的fastdo软件包路径
String GetCurrentFastdoPackage();

// 检测fastdo软件包
// base: string
// include: string
// arch:
//     X64D: string
//     X64R: string
//     X86D: string
//     X86R: string
bool CheckFastdoPackage( Mixed * packInfo );

// 扫描系统内的软件安装信息，获取安装路径
// { software_name1: install_path1, software_name2: install_path2, ... }
bool ScanSoftwareInstalledInfo( String const & strRegexSoftwareName, Mixed * installedColl );

// 扫描编译器安装路径
bool ScanCompilerInstallPath( String const & strRegexSoftwareName, String * compilerName, String * installPath );

// 检测编译器是否安装，获取编译器名和安装路径
bool CheckCompilerInfo( String const & strRegexSoftwareName, Mixed * compilerInfo );

// 检测第三方库是否安装
bool CheckThirdpartiesLibs( StringArray const & libs, Mixed * libsAllInfo );

// 检测环境变量
//{
//    vars: {},
//    arch: {
//        X64D: false,
//        X64R: false,
//        X86D: false,
//        X86R: false
//    },
//    check: false
//}
bool CheckEnvVars( Mixed * info );

// 注册变量
bool RegisterVars( Mixed const & packInfo, Mixed const & registerVars );

// 修改ecp.conf文件中编译器启动脚本路径的配置VSToolsBat
bool ModifyEcpConfig( Mixed const & configs );

// 查找FastDo的IIS设置，包括模块处理器设置和fcgi应用程序池
bool CheckWebServerConfig( Mixed * configInfo );

// 配置IIS
bool ModifyWebServerConfig( Mixed const & configs );
