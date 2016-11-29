#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T11:37:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = XML_Prototype_1
TEMPLATE = app


SOURCES += main.cpp\
    system.cpp \
    block.cpp \
    wire.cpp \
    util.cpp \
    pvar.cpp \
    port.cpp \
    unparsed.cpp \
    mainwindow.cpp

HEADERS  += \
    system.h \
    block.h \
    wire.h \
    util.h \
    pvar.h \
    port.h \
    unparsed.h \
    mainwindow.h

FORMS    += \
    mainwindow.ui

DISTFILES += \
    TODOs.txt
