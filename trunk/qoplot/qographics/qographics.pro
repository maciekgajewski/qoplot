TEMPLATE = lib

CONFIG += staticlib \
debug \
exceptions \
x11
CONFIG -= release

TARGET = qographics

HEADERS += object.h \
root.h \
matrix.h
SOURCES += object.cpp \
root.cpp \
matrix.cpp
