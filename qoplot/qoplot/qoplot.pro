######################################################################
# Automatically generated by qmake (2.01a) Mon Jun 16 12:33:51 2008
######################################################################

TEMPLATE = app
TARGET = qoplot
DESTDIR =../out

DEPENDPATH += .

# Input
HEADERS += \
 plotapp.h \
 op_com.h \
 command.h \
 interpreter.h
SOURCES += \
	main.cpp \
 plotapp.cpp \
 op_com.cpp \
 command.cpp \
 interpreter.cpp

LIBS += ../qographics/libqographics.a

TARGETDEPS += ../qographics/libqographics.a

INCLUDEPATH += ../qographics \
  .
