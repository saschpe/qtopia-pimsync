qtopia_project(external stub)
depends(3rdparty/libraries/curl)
 
# Overwrite 'clean' target to provide custom version
clean.commands = bash clean.sh
linux-x86-g++ {
    funambol_ext.commands = bash build_x86.sh
}
linux-generic-g++ {
    funambol_ext.commands = bash build_x86.sh
}
linux-greenphone-g++ {
    funambol_ext.commands = bash build_gp.sh
}

QMAKE_EXTRA_TARGETS += funambol_ext clean
PRE_TARGETDEPS      += funambol_ext

# We want to install our externally built libs
libs.commands = $(COPY) lib/libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so.3.0.0; \
                ln -fs libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so; \
                ln -fs libsync4j.so.3.0.0 $(INSTALL_ROOT)/lib/libsync4j.so.3
libs.path     = /lib
INSTALLS     += libs

idep(INCLUDEPATH += $$system(pwd)/include/sync4j/common)
idep(LIBS        += -L$$system(pwd)/lib -lsync4j)
