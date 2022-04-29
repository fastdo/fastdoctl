AUTOMAKE_OPTIONS = foreign
CXXFLAGS = -O2 --std=c++11
CPPFLAGS += -I../winux/include -I../eienml/include

bin_PROGRAMS = fastdoctl

fastdoctl_SOURCES = fastdoctl_main.cpp
fastdoctl_LDADD = -lwinux -leienml
fastdoctl_LDFLAGS = -L../winux/src/.libs -L../eienml/src/.libs -Wl,-rpath -Wl,../lib

configdir = @bindir@

config_DATA = \
    fastdoctl_readme.txt

EXTRA_DIST = $(config_DATA)
