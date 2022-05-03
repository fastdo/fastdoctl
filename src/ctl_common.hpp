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

// Windows错误代码转错误串
SimpleHandle<char *> GetErrorStr( uint32 err );

// 获取操作系统版本串
String GetOsVersion();

// 检测编译器是否安装
bool CheckCompiler( String * installedPath );

// 检测第三方库是否安装
bool CheckThirdpartiesLibs();

// 检测PATH环境变量
bool CheckPathEnvVar();

// 修改ecp.conf文件中编译器启动脚本路径的配置VSToolsBat

// 配置IIS