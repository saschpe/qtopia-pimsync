qtopia_project(qtopia app)
depends(libraries/qtopiapim)
TARGET            = synczilla
CONFIG           += qtopia_main
CONFIG           += no_quicklaunch
CONFIG           += debug            # It's not debug it's a feature
CONFIG           += no_singleexec    # Funambol client API license restrictions (can be resolved
                                     # by buying a commercial license)

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

linux-x86-g++ {
    PATH_FUNAMBOL = 3rdparty/libraries/funambol/x86
    PATH_CURL     = 3rdparty/libraries/curl/x86
}
linux-generic-g++ {
    PATH_FUNAMBOL = 3rdparty/libraries/funambol/x86
    PATH_CURL     = 3rdparty/libraries/curl/x86
}
linux-greenphone-g++ {
    PATH_FUNAMBOL = 3rdparty/libraries/funambol/gp
    PATH_CURL     = 3rdparty/libraries/curl/gp
}

INCLUDEPATH      += $${PATH_FUNAMBOL}/include/sync4j/common
LIBS             += -L$${PATH_FUNAMBOL}/lib -L$${PATH_CURL}/lib -lsync4j -lcurl
libs.commands     = $(COPY) $${PATH_FUNAMBOL}/lib/libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so.3.0.0; \
                    ln -fs libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so; \
                    ln -fs libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so.3; \
                    $(COPY) $${PATH_CURL}/lib/libcurl.so.4.0.1 $(INSTALL_ROOT)/lib/libcurl.so.4.0.1; \
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
help.files        = synczilla.html
help.hint         = help
INSTALLS         += help

pkg.name          = synczilla
pkg.desc          = A PIM synchronization tool
pkg.version       = 1.0
pkg.maintainer    = speilick@trolltech.com
pkg.license       = GPL
pkg.domain        = trusted
