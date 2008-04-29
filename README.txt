=========
SyncZilla
=========

SyncZilla let's you synchronize your contacts, events and appointments with your
favorite groupware software solution or groupware web-service. Every SyncML-capable
service offering should work with SyncZilla.


Optional Prerequisites
======================

Remark: 
    These preparations steps should not be mandatory since the default
    build routines already handle prerequisites building.

SyncZilla extensivly uses the Qt toolkit version 4.4 and the Qtopia
phone edition allowing embedded development with Qt (as well as providing
distinct phone features). Qt should be available pre-built for your platform,
see `Trolltech Qt homepage`__ for further infos.

Qtopia phone edition version 4.3.1 has to be built from source for your 
specific target platform, see `Trolltech Qtopia homepage`__ for further infos
on how to extract and build it correctly.

Default build scripts for libcurl and Funambol C++ Client API are provided,
the necessray steps depend on the target platform you want to build for.

Prepare and build prerequisites for a x86 target:

	$ cd 3rdparty/libraries/curl/
	$ bash build_x86.sh
	$ cd ../funambol
	$ bash build_x86.sh

Prepare and build prerequisites for a greenphone target:

	$ cd 3rdparty/libraries/curl/
	$ bash build_gp.sh
	$ cd ../funambol
	$ bash build_gp.sh


__ http://trolltech.com/products/qt/downloads
__ http://trolltech.com/products/qtopia/downloads


Install and test
================

For the x86 emulator (QVFb) you have to start the emulator first:

	$ $QPE_X86_BUILDDIR/bin/runqtopia

Then build the project for the x86 emulator and/or to have it installed
in the Qtopia flash-image (for an embedded device) you have to do
these steps:

	$ $QPE_X86_BUILDDIR/bin/qtopiamake
	$ make
	$ make install

You should then be able to select the application in the Qtopia user interface
application selector (an initial restart may be necessary to inform Qtopia of 
the new application).

Or to build a package for the greenphone (physical embedded device) do the
following steps (a Qtopia phone edition build for greenphone target is needed):

	$ $QPE_GP_BUILDDIR/bin/qtopiamake
	$ make
	$ make package
	$ $QPE_GP_BUILDDIR/scripts/greenphone-sdk/scripts/gph -i    

Remark: 
    Using the application as a package is currently unsupported due to some
    limitations with the Qtopia content APIs.


Example configuration profiles
==============================

These act as a reference, since they are shipped as default configuration profiles.

Name:		Funambol DS server
Url:		http://localhost:8080/funambol/ds
Calendar:	event
Contacts:	card
Tasks:		task
Notes:		?

Name:		myFUNAMBOL web-service
Url:		http://my.funambol.com/sync
Calendar:	event	
Contacts:	card
Tasks:		task
Notes:		?

Name:		ScheduleWorld web-service
Url:      	http://sync.scheduleworld.com/funambol/ds
Calendar: 	cal
Contacts: 	card
Tasks:    	task
Notes:    	note

Name:		mobical web-service
Url:		http://www.mobical.net/sync/server
Calendar:	cal	(or caltask if tasks&calendar have same database)
Contacts:	con
Tasks:		task
Notes:		vnote (or pnote if errors)


Authors
=======

Sascha Peilicke <sascha.peilicke@trolltech.com>


License
=======

Copyright (C) 2007-2008 TROLLTECH ASA. All rights reserved.

This file is part of the Phone Edition of the Qtopia Toolkit.

$TROLLTECH_DUAL_LICENSE$

This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

Note that 3rdparty libraries may have different licensing terms.
