README
======

There is no other solution which uses SyncML on the Qtopia platform. It's advantage is the 
adoption of an widely used industry standard and thus should be able to sync with most 
SyncML-capable groupware solutons given proper configuration.


Content of delivery
===================

The application is delivered as source code together with all 3rd-party dependencies integrated
for easy deployment.

pimsync/src/                 - Complete application source code
pimsync/data/                - Help files, .desktop file and other content used by the application
pkg/                         - Generated QPK packages will be stored here
3rdparty/                    - Necessary dependencies (see GS_INSTALL.txt for details)
3rdparty/libraries/funambol/ - Funambol C++ client API (SyncML protocol implementation)
3rdparty/libraries/curl/     - Libcurl HTTP transport layer implementation (Funambol dependency)

The contents in the 3rd-party folder belong to their respective owners and fall under their 
licensing terms. All other content, sources and documentation belong to Trolltech ASA.


User guide
==========

The application has to be built from source and integrated into the Qtopia flash images, it can
then be used together with the default configuration profiles provided to sync against a locally
installed Funambol DS Server (see the project's page for installation instructions). Syncing
against a selection of groupware web-services is also possible but a working account might be 
needed, see README.txt for web-service configuration profiles. 

The same examples can be shown on the greenphone device, it is possible to sync with the locally
installed groupware server via the cable or to sync to the web via internet access (GPRS, WLAN, 
GSM, Bluetooth DUN, etc.).


Required environment
====================

Qtopia Phone Edition version 4.3.1 + SDK
