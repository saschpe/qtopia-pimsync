#!/bin/bash
#
# This script must be run from $CURL_BASE_DIR.
#
echo "Executing x86 build script"

# Check if we already built for this target, run clean.sh to reset everything.
if [ -d lib/ ]; then
    echo "Target already built, done executing x86 build script"
    exit 0; 
fi

DIR_PREFIX=$PWD

rm -rf curl-7.18.1
tar xjf curl-7.18.1.tar.bz2
cd curl-7.18.1
./configure --prefix=$DIR_PREFIX --disable-manual --disable-telnet --disable-ldap \
            --disable-ldaps --disable-tftp --disable-dict --disable-verbose --disable-file \
            --disable-ftp --disable-debug --disable-sspi --disable-ares #--without-libssh2
make
make install
cd ..
rm -rf share
strip lib/libcurl.so.4.0.1

echo "Done executing x86 build script"
exit 0
