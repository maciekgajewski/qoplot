
# Check octave presence
message("Checking octave version")
system( octave-config -v ) {
} else {
	error("No octave found")
}

# Get octave params
OCTINCLUDEDIR = $$system( octave-config -p OCTINCLUDEDIR )
OCTLIBDIR = $$system( octave-config -p OCTLIBDIR )

INCLUDEPATH += $$OCTINCLUDEDIR
LIBS += -L$${OCTLIBDIR} -loctave
