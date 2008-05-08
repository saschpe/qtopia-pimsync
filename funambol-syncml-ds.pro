qtopia_project(subdirs)
#
# Configure here the desired functionality for QtopiaSync suite. The 
# following features are available:
#
#     - PIM synchronisation over SyncML (OMA DS)


# The 3rd-party dependencies for all the components are located here.
# These dependencies may have their own licenses, see the corresponding
# documentation for details.
#
SUBDIRS += 3rdparty 


# Provides OMA (SyncML) DS client capablitiles. Data synchronisation allows
# exchanging phone contacts. tasks and appointments with a remote DS server.
#
# Requires: 3rdparty
#
SUBDIRS += pimsync
