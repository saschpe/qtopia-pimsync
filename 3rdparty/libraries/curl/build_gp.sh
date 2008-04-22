#!/bin/bash
#
# This script must be run from $CURL_BASE_DIR.
# Requires a valid arm-linux toolchain installed, customize ARM_CC path as needed.
#
echo "Executing Greenphone build script"

DIR_PREFIX=$PWD/gp
DIR_INCLUDE=$DIR_PREFIX/include
DIR_LIB=$DIR_PREFIX/lib
DIR_SHARED=$DIR_PREFIX/shared
ARM_CC=/opt/toolchains/greenphone/gcc-4.1.1-glibc-2.3.6/arm-linux/bin/arm-linux-gcc

rm -rf curl-7.18.1
tar xjf curl-7.18.1.tar.bz2
cd curl-7.18.1
./configure --prefix=$DIR_PREFIX --includedir=$DIR_INCLUDE --libdir=$DIR_LIB --host=arm-linux CC=$ARM_CC --disable-manual
make
make install
cd ..
rm -rf x86/share

echo "Done executing Greenphone build script"
exit 0
