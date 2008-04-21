#!/bin/bash
#
# This script must be run from $FUNAMBOL_BASE_DIR
#

echo "Executing POSIX clean script"

DIR_PREFIX=$PWD/x86
DIR_INCLUDE=$DIR_PREFIX/include
DIR_LIB=$DIR_PREFIX/lib
DIR_SHARE=$DIR_PREFIX/share

rm -rf $DIR_INCLUDE $DIR_LIB $DIR_SHARE

cd build
rm -rf autotools/
tar xzvf autotools.tgz

echo "Done executing POSIX clean script"
exit 0
