qtopia_project(qtopia app)
depends(libraries/qtopiapim)
TARGET            = synczilla
CONFIG           += qtopia_main
CONFIG           += no_quicklaunch
CONFIG           += debug            # It's not debug it's a feature
CONFIG           += no_singleexec    # Funambol client API license restrictions

HEADERS          += src/synczilla.h \
                    src/syncprofile.h \
                    src/configscreen.h \
                    src/syncml/base.h \
                    src/syncml/syncclient.h \
                    src/syncml/abstractsyncsource.h \
                    src/syncml/appointmentsyncsource.h \
                    src/syncml/contactsyncsource.h \
                    src/syncml/tasksyncsource.h
SOURCES          += src/main.cpp \
                    src/synczilla.cpp \
                    src/syncprofile.cpp \
                    src/configscreen.cpp \
                    src/syncml/syncclient.cpp \
                    src/syncml/abstractsyncsource.cpp

INCLUDEPATH      += ./3rdparty/libraries/funambol/include/sync4j/common


linux-x86-g++ {
    LIBS             += -L3rdparty/libraries/funambol/x86/lib -L3rdparty/libraries/curl/x86/lib 
    libs.commands     = $(COPY) 3rdparty/libraries/funambol/x86/lib/libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so.3.0.0; \
                        $(COPY) 3rdparty/libraries/curl/x86/lib/libcurl.so.4.0.1 $(INSTALL_ROOT)/lib/libcurl.so.4.0.1
}
linux-generic-g++ {
    LIBS             += -L3rdparty/libraries/funambol/x86/lib -L3rdparty/libraries/curl/x86/lib 
    libs.commands     = $(COPY) 3rdparty/libraries/funambol/x86/lib/libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so.3.0.0; \
                        $(COPY) 3rdparty/libraries/curl/x86/lib/libcurl.so.4.0.1 $(INSTALL_ROOT)/lib/libcurl.so.4.0.1
}
linux-greenphone-g++ {
    LIBS             += -L3rdparty/libraries/funambol/gp/lib -L3rdparty/libraries/curl/gp/lib 
    libs.commands     = $(COPY) 3rdparty/libraries/funambol/gp/lib/libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so.3.0.0; \
                        $(COPY) 3rdparty/libraries/curl/gp/lib/libcurl.so.4.0.1 $(INSTALL_ROOT)/lib/libcurl.so.4.0.1
}
linux-omap2430-g++ {
    #nothing here for now
}


LIBS             += -lsync4j -lcurl
libs.commands    += ln -fs libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so; \
                    ln -fs libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so.3; \
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
pkg.version       = 0.2
pkg.maintainer    = Trolltech (www.trolltech.com)
pkg.license       = GPL
pkg.domain        = trusted
