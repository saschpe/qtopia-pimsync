#!/bin/bash
#
# This script must be run from $FUNAMBOL_BASE_DIR
#

echo "Executing POSIX clean script"

DIR_PREFIX=$PWD/x86
DIR_INCLUDE=$DIR_PREFIX/include
DIR_LIB=$DIR_PREFIX/lib
DIR_BIN=$DIR_PREFIX/bin
DIR_SHARED=$DIR_PREFIX/share

rm -rf $DIR_INCLUDE $DIR_LIB $DIR_SHARED $DIR_BIN
rm -rf curl-7.18.1

echo "Done executing POSIX clean script"
exit 0
