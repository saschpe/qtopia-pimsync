README
======

This document gives general information about the partner solution.


Provider
========

Funambol Inc.


Functionality overview
======================

PIM synchronisation (OMA DS) bases on SyncML.


Benefits
========

There is no other solution which uses SyncML on the Qtopia platform. It's advantage is the adoption of an
widely used industry standard. It should be able to sync with most SyncML-capable groupware solutons given
proper configuration.


Content of delivery
===================

The application is delivered as source code together with all 3rd-party dependencies integrated for easy
deployment.

pimsync/src/                 - Complete application source code
pimsync/data/                - Help files, .desktop file and other content used by the application
3rdparty/                    - Necessary dependencies (see GS_INSTALL.txt for details)
3rdparty/libraries/funambol/ - Funambol C++ client API (SyncML protocol implementation)
3rdparty/libraries/curl/     - Libcurl HTTP transport layer implementation (Funambol dependency)

The contents in the 3rd-party folder belong to their respective owners and fall under their licensing
terms. All other content, sources and documentation belong to Trolltech ASA.


Other available documents
=========================

GS_INSTALL.txt       - Installation guide
GS_RELEASE_NOTES.txt - Release Notes
README.txt           - Description, License notes, description of prerequisites and installation procedure


User guide
==========

The application has to be built from source and integrated into the Qtopia flash images, it can then be used together with 
the default configuration profiles provided to sync against a locally installed Funambol DS Server (see the project's page
for installation instructions). Syncing against a selection of groupware web-services is also possible but a working account
might be needed, see README.txt for web-service configuration profiles. 

The same examples can be shown on the greenphone device, it is possible to sync with the locally installed groupware server
via the cable (not that OBEX send is not supported currently) or to sync to the web via internet access (GPRS, WLAN, ...).


Required environment
====================

QPE 4.3.1 + SDK (see master document for further infos)
