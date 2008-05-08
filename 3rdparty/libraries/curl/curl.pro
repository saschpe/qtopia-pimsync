qtopia_project(external stub)
 
# Overwrite 'clean' target to provide custom version
clean.commands = (bash clean.sh)
linux-x86-g++ {
    curl_ext.commands = (bash build_x86.sh)
}
linux-generic-g++ {
    curl_ext.commands = (bash build_x86.sh)
}
linux-greenphone-g++ {
    curl_ext.commands = (bash build_gp.sh)
}

QMAKE_EXTRA_TARGETS += curl_ext clean
PRE_TARGETDEPS      += curl_ext

# We want to install our externally built libs
libs.commands = $(COPY) lib/libcurl.so.4.0.1 $(INSTALL_ROOT)/lib/libcurl.so.4.0.1; \
                ln -fs libcurl.so.4.0.1 $(INSTALL_ROOT)/lib/libcurl.so; \
                ln -fs libcurl.so.4.0.1 $(INSTALL_ROOT)/lib/libcurl.so.4
libs.path     = /lib
INSTALLS     += libs

idep(LIBS += -L$$system(pwd)/lib -lcurl)
