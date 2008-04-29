qtopia_project(qtopia app)
depends(libraries/qtopiapim)
TARGET            = synczilla
CONFIG           += qtopia_main
CONFIG           += no_quicklaunch
CONFIG           += no_singleexec    # Funambol client API license restrictions (can be resolved
                                     # by buying a commercial license)
CONFIG           += release          # Ignored if 'debug' is also specified
#CONFIG           += debug

HEADERS          += src/synczilla.h \
                    src/syncprofile.h \
                    src/configscreen.h \
                    src/syncml/base.h \
                    src/syncml/syncclient.h \
                    src/syncml/abstractsyncsource.h \
                    src/syncml/contactsyncsource.h \
                    src/syncml/appointmentsyncsource.h \
                    src/syncml/tasksyncsource.h \
                    src/syncml/notesyncsource.h
SOURCES          += src/main.cpp \
                    src/synczilla.cpp \
                    src/syncprofile.cpp \
                    src/configscreen.cpp \
                    src/syncml/syncclient.cpp \
                    src/syncml/abstractsyncsource.cpp

#
# Platform specific configuration and additional rules for the Makefile
# ('make curl' and 'make funambol'). TARGET also depends on these.
#
linux-x86-g++ {
    PATH_FUNAMBOL     = 3rdparty/libraries/funambol/x86
    PATH_CURL         = 3rdparty/libraries/curl/x86
	curl.commands     = (cd 3rdparty/libraries/curl && bash build_x86.sh)
	funambol.commands = (cd 3rdparty/libraries/funambol && bash build_x86.sh)
}
linux-generic-g++ {
    PATH_FUNAMBOL     = 3rdparty/libraries/funambol/x86
    PATH_CURL         = 3rdparty/libraries/curl/x86
	curl.commands     = (cd 3rdparty/libraries/curl && bash build_x86.sh)
	funambol.commands = (cd 3rdparty/libraries/funambol && bash build_x86.sh)
}
linux-greenphone-g++ {
    PATH_FUNAMBOL     = 3rdparty/libraries/funambol/gp
    PATH_CURL         = 3rdparty/libraries/curl/gp
	curl.commands     = (cd 3rdparty/libraries/curl && bash build_gp.sh)
	funambol.commands = (cd 3rdparty/libraries/funambol && bash build_gp.sh)
}
funambol.depends      = curl
QMAKE_EXTRA_TARGETS  += curl funambol
##PRE_TARGETDEPS       += curl funambol

#
# REMARK: The 'libs' install target might not need to deploy libcurl in Qtopia-4.4 because 
#         it could be already shipped. This version of libcurl is stripped to the absolute 
#         minimum and has a small footprint (supported features: HTTP and SSL).
#
#         If the above applies comment out the second 'libs.commands' rule to not install libcurl.
#         It is recommended to keep the dependency in the project so that it can be used at build-time.
#
INCLUDEPATH      += $${PATH_FUNAMBOL}/include/sync4j/common
LIBS             += -L$${PATH_FUNAMBOL}/lib -L$${PATH_CURL}/lib -lsync4j -lcurl
libs.commands     = $(COPY) $${PATH_FUNAMBOL}/lib/libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so.3.0.0; \
                    ln -fs libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so; \
                    ln -fs libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so.3
libs.commands    += $(COPY) $${PATH_CURL}/lib/libcurl.so.4.0.1 $(INSTALL_ROOT)/lib/libcurl.so.4.0.1; \
                    ln -fs libcurl.so.4.0.1 $(INSTALL_ROOT)/lib/libcurl.so; \
                    ln -fs libcurl.so.4.0.1 $(INSTALL_ROOT)/lib/libcurl.so.4
libs.path         = /lib
INSTALLS         += libs


desktop.files     = data/synczilla.desktop
desktop.path      = /apps/Applications
desktop.trtarget  = synczilla-nct
desktop.hint      = desktop nct
INSTALLS         += desktop

pics.files        = data/pics/*
pics.path         = /pics/synczilla
pics.hint         = pics
INSTALLS         += pics

help.source       = data/help
help.files        = *.html
help.hint         = help
INSTALLS         += help

pkg.name          = synczilla
pkg.desc          = A PIM synchronization tool
pkg.version       = 1.0
pkg.maintainer    = Sascha Peilicke <speilick@trolltech.com>
pkg.license       = GPL
pkg.domain        = trusted
