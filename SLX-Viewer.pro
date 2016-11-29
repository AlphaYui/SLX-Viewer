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
    mainwindow.cpp \
    General/util.cpp \
    Main/block.cpp \
    Main/port.cpp \
    Main/pvar.cpp \
    Main/system.cpp \
    Main/unparsed.cpp \
    Main/wire.cpp \
    UI/mainwindow.cpp

HEADERS  += \
    system.h \
    block.h \
    wire.h \
    util.h \
    pvar.h \
    port.h \
    unparsed.h \
    mainwindow.h \
    General/util.h \
    Main/block.h \
    Main/port.h \
    Main/pvar.h \
    Main/system.h \
    Main/unparsed.h \
    Main/wire.h \
    UI/mainwindow.h

FORMS    += \
    mainwindow.ui \
    UI/mainwindow.ui

DISTFILES += \
    TODOs.txt \
    Notes/TODOs.txt
