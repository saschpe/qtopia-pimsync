qtopia_project(subdirs)
CONFIG += build_all_dirs

## Do not change the order of subdirs, this is necessary to resolve
## depencies for depends() is unsuitable because of that:
##
##   There is no support for depending on a particular project in a 
##   particular project root but such support may appear in the future.
##
#SUBDIRS = curl funambol
#CONFIG += ordered
