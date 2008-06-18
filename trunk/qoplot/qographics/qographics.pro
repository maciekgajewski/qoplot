TEMPLATE = lib

CONFIG += staticlib \
debug \
exceptions \
x11
CONFIG -= release

TARGET = qographics

HEADERS += object.h \
root.h \
matrix.h \
 figurewindow.h \
 figure.h \
 exceptions.h
SOURCES += object.cpp \
root.cpp \
matrix.cpp \
 figurewindow.cpp \
 figure.cpp
FORMS += figurewindow.ui

