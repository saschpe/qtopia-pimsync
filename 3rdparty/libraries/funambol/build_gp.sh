#!/bin/bash
#
# This script must be run from $FUNAMBOL_BASE_DIR. Requires a valid arm-linux 
# toolchain installed, customize DIR_ARM_TOOLCHAIN_BIN as needed.
#
echo "Executing Greenphone build script"

# Check if we already built for this target, run clean.sh to reset everything.
if [ -d lib/ ]; then
    echo "Target already built, done executing Greenphone build script"
    exit 0; 
fi

DIR_PREFIX=$PWD
DIR_CURL_BIN=$DIR_PREFIX/../curl/bin
DIR_ARM_TOOLCHAIN_BIN=/opt/toolchains/greenphone/gcc-4.1.1-glibc-2.3.6/arm-linux/bin

rm -rf funambol
tar xjf funambol-7.tar.bz2
cd funambol/build/autotools
${LIBTOOLIZE:-libtoolize} -c -f
aclocal
autoheader
automake -a -c -f
autoconf -f
export PATH=$PATH:$DIR_CURL_BIN:$DIR_ARM_TOOLCHAIN_BIN
./configure --host=arm-linux --prefix=$DIR_PREFIX
make
make install
cd ../../..
$DIR_ARM_TOOLCHAIN_BIN/arm-linux-strip lib/libfunambol.so.3.0.0

echo "Done executing Greenphone build script"
exit 0
