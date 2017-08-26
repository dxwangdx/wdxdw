#-------------------------------------------------
#
# Project created by QtCreator 2016-11-01T08:36:59
#
#-------------------------------------------------

QT       += core gui
QT += network
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    enrollwindow.cpp \
    sclicklabel.cpp \
    roomwindow.cpp \
    myroomwindow.cpp \
    videosurface.cpp

HEADERS  += mainwindow.h \
    enrollwindow.h \
    sclicklabel.h \
    package.h \
    roomwindow.h \
    myroomwindow.h \
    videosurface.h

FORMS    += mainwindow.ui \
    enrollwindow.ui \
    roomwindow.ui \
    myroomwindow.ui
