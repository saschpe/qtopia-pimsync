qtopia_project(subdirs)

# The 3rd-party dependencies for all the components are located here.
# These dependencies may have their own licenses, see the corresponding
# documentation for details.
#
SUBDIRS += 3rdparty 

# Provides OMA (SyncML) DS client capabilities. Data synchronisation allows
# to exchange phone contacts. tasks and appointments with a remote DS server.
#
# Requires: 3rdparty
#
SUBDIRS += pimsync
