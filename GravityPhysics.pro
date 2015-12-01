#-------------------------------------------------
#
# Project created by QtCreator 2015-11-30T15:42:03
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GravityPhysics
TEMPLATE = app

INCLUDEPATH += include/

SOURCES += src/main.cpp\
        src/GravityMainWindow.cpp \
    src/GravityMainWindow.cpp \
    src/main.cpp \
    src/BallObject.cpp

HEADERS  += include/GravityMainWindow.h \
    include/GravityMainWindow.h \
    include/BallObject.h \
    include/cgcommon.h

FORMS    += forms/gravitymainwindow.ui

DISTFILES +=
