QT += core
QT -= gui

CONFIG += c++11

TARGET = ioprj
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    gridstorage.cpp \
    subregion.cpp \
    gridcell.cpp

HEADERS += \
    gridstorage.h \
    subregion.h \
    contains.h \
    gridcell.h
