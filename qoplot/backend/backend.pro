include( octave.pri )

TEMPLATE = lib
TARGET =qobackend
system( ln -sf libqobackend.so qobackend.oct )

CONFIG += dll \
 debug
QT += svg

SOURCES = main.cpp\
	figurewindow.cpp \
 backend.cpp \
 plotevent.cpp \
 figuremanager.cpp \
 converters.cpp \
 uiitem.cpp \
 axesitem.cpp \
 systeminfo.cpp \
 textitem.cpp \
 plotitem.cpp

HEADERS = figurewindow.h \
 backend.h \
 plotevent.h \
 eventtypes.h \
 figuremanager.h \
 converters.h \
 uiitem.h \
 axesitem.h \
 systeminfo.h \
 textitem.h \
 plotitem.h

FORMS = figurewindow.ui
CONFIG -= release

