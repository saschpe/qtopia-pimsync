#!/bin/bash
#
# This script must be run from $FUNAMBOL_BASE_DIR
#

echo "Executing POSIX build script"

DIR_PREFIX=$PWD
DIR_INCLUDE=$DIR_PREFIX/include
DIR_LIB=$DIR_PREFIX/lib

DIR_CURL_BIN=$DIR_PREFIX/../curl/bin
OLD_PATH=$PATH

cd build/autotools

${LIBTOOLIZE:-libtoolize} -c -f
aclocal
autoheader
automake -a -c -f
autoconf -f

export PATH=$PATH:$DIR_CURL_BIN
echo $PATH

./configure --prefix=$DIR_PREFIX --includedir=$DIR_INCLUDE --libdir=$DIR_LIB
make
make install

export PATH=$OLD_PATH
echo $PATH

echo "Done executing POSIX build script"
exit 0
