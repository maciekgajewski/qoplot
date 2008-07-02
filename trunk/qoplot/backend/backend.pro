include( octave.pri )

TEMPLATE = lib
TARGET =qobackend
system( ln -sf libqobackend.so qobackend.oct )

CONFIG += dll
QT += svg

SOURCES = main.cpp\
	figurewindow.cpp \
 backend.cpp \
 plotevent.cpp \
 figuremanager.cpp

HEADERS = figurewindow.h \
 backend.h \
 plotevent.h \
 eventtypes.h \
 figuremanager.h

FORMS = figurewindow.ui
