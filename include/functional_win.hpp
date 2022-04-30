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

#include <tchar.h>


String GetOsVersion();