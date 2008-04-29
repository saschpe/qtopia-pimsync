#!/bin/bash
#
# This script must be run from $FUNAMBOL_BASE_DIR.
#
echo "Executing x86 build script"

# Check if we already built for this target, run clean.sh to reset everything.
if [ -d x86/lib/ ]; then
	echo "Target already built, done executing x86 build script"
	exit 0; 
fi

DIR_PREFIX=$PWD/x86
DIR_CURL_BIN=$DIR_PREFIX/../../curl/x86/bin

rm -rf funambol
tar xjf funambol.tar.bz2
cd funambol/build/autotools
${LIBTOOLIZE:-libtoolize} -c -f
aclocal
autoheader
automake -a -c -f
autoconf -f
export PATH=$PATH:$DIR_CURL_BIN
./configure --prefix=$DIR_PREFIX
make
make install

echo "Done executing x86 build script"
exit 0
