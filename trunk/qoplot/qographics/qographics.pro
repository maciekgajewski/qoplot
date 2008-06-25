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
 enum.h \
 color.h \
 axes.h \
 axesitem.h \
 uiobject.h \
 text.h \
 uiitem.h \
 textitem.h \
 plotobject.h \
 plotitem.h \
 line.h \
 lineitem.h \
 image.h \
 imageitem.h
SOURCES += object.cpp \
root.cpp \
matrix.cpp \
 figurewindow.cpp \
 figure.cpp \
 enum.cpp \
 color.cpp \
 axes.cpp \
 axesitem.cpp \
 uiobject.cpp \
 text.cpp \
 uiitem.cpp \
 textitem.cpp \
 plotobject.cpp \
 plotitem.cpp \
 line.cpp \
 lineitem.cpp \
 image.cpp \
 imageitem.cpp
FORMS += figurewindow.ui

QT += svg

