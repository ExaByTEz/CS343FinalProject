#-------------------------------------------------
#
# Project created by QtCreator 2015-11-30T15:42:03
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GravityPhysics
TEMPLATE = app

# Specify the opengl libraries explicitly (qmake doesn't include them on windows)
win32 {
    LIBS += -lopengl32 -lglu32
}

INCLUDEPATH += include/

SOURCES += src/main.cpp\
        src/GravityMainWindow.cpp \
    src/GravityMainWindow.cpp \
    src/main.cpp \
    src/BallObject.cpp \
    src/GL2DDrawingWidget.cpp

HEADERS  += include/GravityMainWindow.h \
    include/GravityMainWindow.h \
    include/BallObject.h \
    include/cgcommon.h \
    include/GL2DDrawingWidget.h

FORMS    += forms/gravitymainwindow.ui

DISTFILES +=
