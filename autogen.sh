#!/bin/sh
aclocal
autoconf
autoheader
#libtoolize --automake --copy
automake --add-missing --copy
