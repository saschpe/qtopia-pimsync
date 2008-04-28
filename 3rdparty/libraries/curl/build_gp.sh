#!/bin/bash
#
# This script must be run from $CURL_BASE_DIR. Requires a valid arm-linux 
# toolchain installed, customize DIR_ARM_TOOLCHAIN_BIN as needed.
#
echo "Executing Greenphone build script"

DIR_PREFIX=$PWD/gp
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
rm -rf x86/share

echo "Done executing Greenphone build script"
exit 0
