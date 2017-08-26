#-------------------------------------------------
#
# Project created by QtCreator 2016-11-01T08:36:10
#
#-------------------------------------------------

QT       += core gui
QT += sql
QT += network
QT += multimedia
QT += multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = server
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    clientsocket.cpp \
    user.cpp \
    dbcreator.cpp \
    userdao.cpp \
    person.cpp \
    roomlist.cpp

HEADERS  += mainwindow.h \
    clientsocket.h \
    package.h \
    user.h \
    dbcreator.h \
    userdao.h \
    person.h \
    roomlist.h

FORMS    += mainwindow.ui
