#!/bin/bash
#
# This script must be run from $FUNAMBOL_BASE_DIR
#

echo "Executing POSIX clean script"

DIR_PREFIX=$PWD
DIR_INCLUDE=$DIR_PREFIX/include
DIR_LIB=$DIR_PREFIX/lib
DIR_BIN=$DIR_PREFIX/bin
DIR_SHARED=$DIR_PREFIX/share

rm -rf $DIR_INCLUDE $DIR_LIB $DIR_SHARED $DIR_BIN
cd curl
make clean

echo "Done executing POSIX clean script"
exit 0
