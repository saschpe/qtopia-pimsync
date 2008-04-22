#!/bin/bash
#
# This script must be run from $FUNAMBOL_BASE_DIR.
#
echo "Executing x86 build script"

DIR_PREFIX=$PWD/x86
DIR_INCLUDE=$DIR_PREFIX/include
DIR_LIB=$DIR_PREFIX/lib
DIR_CURL_BIN=$DIR_PREFIX/../../curl/x86/bin
OLD_PATH=$PATH

rm -rf funambol
tar xjf funambol.tar.bz2
cd build/autotools
${LIBTOOLIZE:-libtoolize} -c -f
aclocal
autoheader
automake -a -c -f
autoconf -f
export PATH=$PATH:$DIR_CURL_BIN
./configure --prefix=$DIR_PREFIX --includedir=$DIR_INCLUDE --libdir=$DIR_LIB
make
make install
export PATH=$OLD_PATH

echo "Done executing x86 build script"
exit 0
