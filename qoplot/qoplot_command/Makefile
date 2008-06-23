LN_S=ln -s
MKOCTFILE=mkoctfile
DESTDIR=../out
SRCDIR=../qoplot

all: $(DESTDIR)/qoplot_command.oct $(DESTDIR)/qoplot_path.oct $(DESTDIR)/qoplot_redraw.oct 

$(DESTDIR)/qoplot_command.oct: op_com.o qoplot_command.o
	$(MKOCTFILE) -v op_com.o qoplot_command.o -o $(DESTDIR)/qoplot_command.oct

qoplot_command.o: qoplot_command.cc
	$(MKOCTFILE) -v -I$(SRCDIR) -c qoplot_command.cc
	
op_com.o: $(SRCDIR)/op_com.cpp $(SRCDIR)/op_com.h
	$(MKOCTFILE) -v -I$(SRCDIR) -o op_com.o -c $(SRCDIR)/op_com.cpp

$(DESTDIR)/qoplot_path.oct: $(DESTDIR)/qoplot_command.oct
	$(LN_S) qoplot_command.oct $(DESTDIR)/qoplot_path.oct

$(DESTDIR)/qoplot_redraw.oct: $(DESTDIR)/qoplot_command.oct
	$(LN_S) qoplot_command.oct $(DESTDIR)/qoplot_redraw.oct

clean:
	rm $(DESTDIR)/qoplot_redraw.oct $(DESTDIR)/qoplot_path.oct $(DESTDIR)/qoplot_command.oct op_com.o qoplot_command.o
