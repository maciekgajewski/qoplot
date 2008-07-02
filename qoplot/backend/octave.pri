# octave params, ripped from mkoctfile

OCT_CXX_FLAGS = -fPIC -mieee-fp
OCT_LFLAGS = -Wl,-Bsymbolic
OCT_INCLUDEPATH = /usr/local/include/octave-3.0.0+ /usr/local/include/octave-3.0.0+/octave /usr/include/freetype2
OCT_LIBS = -L/usr/local/lib/octave-3.0.0+ -L/usr/local/lib \
	-loctinterp -loctave -lcruft -llapack -lblas -lfftw3 -lfftw3f -lreadline -lncurses -ldl \
	-lblas -lhdf5 -lz -lgfortranbegin -lgfortran
	
	
# append cotave params to defaults
QMAKE_CXXFLAGS += $$OCT_CXX_FLAGS
QMAKE_LFLAGS += $$OCT_LFLAGS
INCLUDEPATH += $$OCT_INCLUDEPATH
LIBS += $$OCT_LIBS
