#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.63])
AC_INIT([fastdoctl], [1.0], [zth555@qq.com])
AC_CONFIG_AUX_DIR([build-aux])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/fastdoctl_main.cpp])
AC_CONFIG_HEADERS([config.h])

AC_LANG([C++])
AC_PREFIX_DEFAULT([/usr/local/fastdo])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
# FIXME: Replace `main' with a function in `-leienml':
AC_CHECK_LIB([eienml], [main])
# FIXME: Replace `main' with a function in `-lwinux':
AC_CHECK_LIB([winux], [main])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
