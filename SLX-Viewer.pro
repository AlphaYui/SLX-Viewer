#-------------------------------------------------
#
# Project created by QtCreator 2016-11-15T11:37:11
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SLX-Viewer
TEMPLATE = app


SOURCES += main.cpp\
    General/util.cpp \
    Main/block.cpp \
    Main/port.cpp \
    Main/pvar.cpp \
    Main/system.cpp \
    Main/unparsed.cpp \
    Main/wire.cpp \
    UI/mainwindow.cpp

HEADERS  += \
    General/util.h \
    Main/block.h \
    Main/port.h \
    Main/pvar.h \
    Main/system.h \
    Main/unparsed.h \
    Main/wire.h \
    UI/mainwindow.h

FORMS    += \
    UI/mainwindow.ui

DISTFILES += \
    TODOs.txt \
    Notes/TODOs.txt \
    Tests/blockdiagram.xml \
    Tests/configSet0.xml \
    Tests/configSetInfo.xml \
    Tests/graphicalInterface.xml \
    Tests/stateflow.xml \
    Tests/BallPlate.slx
