QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    adminclass.cpp \
    adminlist.cpp \
    cardclass.cpp \
    database.cpp \
    listclass.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    md5.cpp \
    methods.cpp \
    sets.cpp

HEADERS += \
    adminclass.h \
    adminlist.h \
    cardclass.h \
    database.h \
    listclass.h \
    logindialog.h \
    mainwindow.h \
    md5.h \
    methods.h \
    sets.h

FORMS += \
    logindialog.ui \
    mainwindow.ui \
    methods.ui \
    sets.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
