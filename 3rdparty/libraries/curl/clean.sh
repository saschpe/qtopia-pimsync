#!/bin/bash
#
# This script must be run from $FUNAMBOL_BASE_DIR
#
echo "Executing clean script"

rm -rf include/ lib/ bin/ share/ curl-7.18.1/

echo "Done executing clean script"
exit 0
