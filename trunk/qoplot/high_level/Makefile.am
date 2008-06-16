destinationdir = $(opath)

# path for Octplots' normal m-files; this should *not* lie in Octave's
# LOADPATH, otherwise toggle_octplot becomes useless.
octplotmdir = $(octplotmpath)

destination_SCRIPTS = __contourc__.oct

EXTRA_DIST = __contourc__.cc 

dist_octplotm_DATA = \
area.m   colorbar.m    gcf.m     __nxtplt__.m  __plt__.m     stem.m\
axis.m   colormap.m    grid.m    pareto.m      __pltopt__.m \
barh.m   contourc.m    histh.m   pcolor.m      semilogx.m \
__bar.m  contour.m     __hist.m  pie.m         semilogy.m \
bar.m    freqz_plot.m  hist.m    plot.m        shading.m \
box.m    gca.m         loglog.m  plotyy.m      specgram.m \
hold.m   ishold.m      ohold.m   contourf.m    clabel.m \
caxis.m  findobj.m

############################################################################
### all files built from this point must be explicitly listed in the
### CLEANFILES var at the end of this Makefile -- otherwise make clean
### & make dist won't work !!

ohold.m: hold.m
	$(LN_S) -f hold.m ohold.m

# octfile make rules
.cc.o:
	$(MKOCTFILE) -v -c $<
.cc.oct:
	$(MKOCTFILE) -v $<

# what is built explicitly must also be cleaned explicitly -- all oct files should be here or bad things will happen
# in the distribution !!
CLEANFILES = __contourc__.oct ohold.m 

# create symlinks; as the install command from coreutils can't handle symlinks,
# we link the files at install time, again!
install-data-hook:
	cd $(DESTDIR)$(octplotmdir) &&  \
		$(LN_S) -f hold.m ohold.m 
