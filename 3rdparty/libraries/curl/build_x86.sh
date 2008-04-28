#!/bin/bash
#
# This script must be run from $CURL_BASE_DIR.
#
echo "Executing x86 build script"

DIR_PREFIX=$PWD/x86

rm -rf curl-7.18.1
tar xjf curl-7.18.1.tar.bz2
cd curl-7.18.1
./configure --prefix=$DIR_PREFIX --disable-manual --disable-telnet --disable-ldap \
	--disable-ldaps --disable-tftp --disable-dict --disable-verbose --disable-file \
	--disable-ftp --disable-debug --disable-sspi --disable-ares --without-libssh2
make
make install
cd ..
rm -rf x86/share

echo "Done executing x86 build script"
exit 0
