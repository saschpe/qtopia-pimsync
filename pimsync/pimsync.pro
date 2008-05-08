qtopia_project(qtopia app)
depends(libraries/qtopiapim)
depends(3rdparty/libraries/funambol)
TARGET   = pimsync
CONFIG  += qtopia_main no_quicklaunch

HEADERS += src/pimsync.h \
           src/syncprofile.h \
           src/configscreen.h \
           src/syncml/syncclient.h \
           src/syncml/abstractsyncsource.h \
           src/syncml/contactsyncsource.h \
           src/syncml/appointmentsyncsource.h \
           src/syncml/tasksyncsource.h \
           src/syncml/notesyncsource.h
SOURCES += src/main.cpp \
           src/pimsync.cpp \
           src/syncprofile.cpp \
           src/configscreen.cpp \
           src/syncml/syncclient.cpp \
           src/syncml/abstractsyncsource.cpp

desktop.files    = data/PIMSync.desktop
desktop.path     = /apps/Applications
desktop.trtarget = pimsync-nct
desktop.hint     = desktop nct
INSTALLS        += desktop
pics.files       = data/pics/*
pics.path        = /pics/pimsync
pics.hint        = pics
INSTALLS        += pics
help.source      = data/help
help.files       = pimsync.*
help.hint        = help
INSTALLS        += help

pkg.desc         = PIM synchronization tool
pkg.domain       = trusted
