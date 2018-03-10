QT += core
QT -= gui

CONFIG += c++11

TARGET = ioprj
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    gridregion.cpp \
    gridstorage.cpp \
    subregion.cpp

HEADERS += \
    gridregion.h \
    gridstorage.h \
    subregion.h \
    contains.h
