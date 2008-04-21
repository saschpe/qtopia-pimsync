#!/bin/bash
#
# This script must be run from $CURL_BASE_DIR
#

echo "Executing POSIX build script"

DIR_PREFIX=$PWD
DIR_INCLUDE=$DIR_PREFIX/include
DIR_LIB=$DIR_PREFIX/lib
DIR_SHARED=$DIR_PREFIX/shared

cd curl
./configure --prefix=$DIR_PREFIX --includedir=$DIR_INCLUDE --libdir=$DIR_LIB --disable-manual
make
make install

echo "Done executing POSIX build script"
exit 0
