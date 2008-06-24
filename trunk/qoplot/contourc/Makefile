LN_S=ln -s
MKOCTFILE=mkoctfile
DESTDIR=../high_level

all: $(DESTDIR)/__contourc__.oct

$(DESTDIR)/__contourc__.oct: __contourc__.cc
	$(MKOCTFILE) -v __contourc__.cc -o $(DESTDIR)/__contourc__.oct

	
clean:
	rm $(DESTDIR)/__contourc__.oct
