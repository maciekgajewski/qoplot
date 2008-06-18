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
 exceptions.h \
 enum.h
SOURCES += object.cpp \
root.cpp \
matrix.cpp \
 figurewindow.cpp \
 figure.cpp \
 enum.cpp
FORMS += figurewindow.ui

