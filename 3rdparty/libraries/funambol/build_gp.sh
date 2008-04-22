#!/bin/bash
#
# This script must be run from $FUNAMBOL_BASE_DIR.
# Requires a valid arm-linux toolchain installed, customize ARM_CC path as needed.
#
echo "Executing Greenphone build script"

DIR_PREFIX=$PWD/gp
DIR_INCLUDE=$DIR_PREFIX/include
DIR_LIB=$DIR_PREFIX/lib
DIR_CURL_BIN=$DIR_PREFIX/../../curl/gp/bin
OLD_PATH=$PATH
ARM_CC=/opt/toolchains/greenphone/gcc-4.1.1-glibc-2.3.6/arm-linux/bin/arm-linux-gcc

rm -rf funambol
tar xjf funambol.tar.bz2
cd funambol/build/autotools
${LIBTOOLIZE:-libtoolize} -c -f
aclocal
autoheader
automake -a -c -f
autoconf -f
export PATH=$PATH:$DIR_CURL_BIN
CC=$ARM_CC ./configure --host=arm-linux --prefix=$DIR_PREFIX --includedir=$DIR_INCLUDE --libdir=$DIR_LIB
make
make install
export PATH=$OLD_PATH

echo "Done executing Greenphone build script"
exit 0
