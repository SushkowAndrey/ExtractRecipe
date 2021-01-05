QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    account.cpp \
    dataorganization.cpp \
    log.cpp \
    main.cpp \
    mainwindow.cpp \
    organization.cpp \
    registration.cpp \
    selectingorganization.cpp

HEADERS += \
    account.h \
    checkingstring.h \
    dataorganization.h \
    log.h \
    mainwindow.h \
    organization.h \
    registration.h \
    selectingorganization.h

FORMS += \
    account.ui \
    dataorganization.ui \
    mainwindow.ui \
    organization.ui \
    registration.ui \
    selectingorganization.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
