#!/bin/bash
#
# This script must be run from $CURL_BASE_DIR. Requires a valid arm-linux 
# toolchain installed, customize DIR_ARM_TOOLCHAIN_BIN as needed.
#
echo "Executing Greenphone build script"

# Check if we already built for this target, run clean.sh to reset everything.
if [ -d lib/ ]; then
	echo "Target already built, done executing Greenphone build script"
	exit 0; 
fi

DIR_PREFIX=$PWD
DIR_ARM_TOOLCHAIN_BIN=/opt/toolchains/greenphone/gcc-4.1.1-glibc-2.3.6/arm-linux/bin

rm -rf curl-7.18.1
tar xjf curl-7.18.1.tar.bz2
cd curl-7.18.1
export PATH=$PATH:$DIR_ARM_TOOLCHAIN_BIN
./configure --host=arm-linux --prefix=$DIR_PREFIX --without-random \
	--disable-manual --disable-telnet --disable-ldap --disable-ldaps --disable-tftp \
	--disable-dict --disable-verbose --disable-file --disable-ftp --disable-debug \
	--disable-sspi --disable-ares --without-libssh2
make
make install
cd ..
rm -rf share
$DIR_ARM_TOOLCHAIN_BIN/arm-linux-strip lib/libcurl.so.4.0.1

echo "Done executing Greenphone build script"
exit 0
