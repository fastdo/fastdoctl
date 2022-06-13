AUTOMAKE_OPTIONS = foreign
CXXFLAGS = -O2 --std=c++11
CPPFLAGS += -I../winux/include -I../eienml/include

INCLUDE_FILES = \
    ctl_api_handlers.hpp \
    ctl_common.hpp \
    ctl_ControlCenterApp.hpp \
    ctl_web_handlers.hpp

include_HEADERS = $(INCLUDE_FILES)

bin_PROGRAMS = fastdoctl

fastdoctl_SOURCES = \
    ctl_api_handlers.cpp \
    ctl_common_unix.cpp \
    ctl_ControlCenterApp.cpp \
    ctl_web_handlers.cpp \
    main.cpp

fastdoctl_LDADD = -lwinux -lhttpwrapper -leiennet -leienwebx
fastdoctl_LDFLAGS = -L../winux/src/.libs -L../eienml/src/.libs -Wl,-rpath -Wl,../lib

configdir = @bindir@

config_DATA = 

EXTRA_DIST = \
    $(config_DATA) \
    ctl_common_win.cpp
