#!/bin/bash
#
# This script must be run from $FUNAMBOL_BASE_DIR
#
echo "Executing clean script"

DIR_X86_PREFIX=$PWD/x86
DIR_X86_INCLUDE=$DIR_X86_PREFIX/include
DIR_X86_LIB=$DIR_X86_PREFIX/lib
DIR_X86_SHARE=$DIR_X86_PREFIX/share

DIR_GP_PREFIX=$PWD/gp
DIR_GP_INCLUDE=$DIR_GP_PREFIX/include
DIR_GP_LIB=$DIR_GP_PREFIX/lib
DIR_GP_SHARE=$DIR_GP_PREFIX/share

rm -rf $DIR_X86_INCLUDE $DIR_X86_LIB $DIR_X86_SHARE
rm -rf $DIR_GP_INCLUDE $DIR_GP_LIB $DIR_GP_SHARE
rm -rf funambol

echo "Done executing clean script"
exit 0
