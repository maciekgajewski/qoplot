What's this
===========

This is qoplot - plotting system for octave.

It's based on octplot. Like octplot (and unlike gnuplot) - it emulates Matlab's(TM) Handle
Graphics(TM). Unlike octplot, uses Qt and all it's features.

I write this becouse I need plotting system able to driwing images and basic
plots, and I find UI controls on plot figures useful.

Current features:

- 2D plot objects - axes, figures, text, lines, patches, images, legends, with
  settable properties.

- Printing to PS, PDF, PNG, SVG and JPG

Planned features for upcoming 0.1 release

- basing plotting commands implemented, 2D plot objects implemented, support
  for richer user interaction via basic UI Controls.

What's here
============

Stuff inherited after octplot:
- demos/
- high_level/
- tests/

And:

- out/ - former octplot's src dir. Contains .m files and output from compilation gets there
- qoplot_command/ - octave command impelemntation, former octplot_command
- qographics/ - graphics susbsytem implementation used by qoplot
- qoplot/ - qoplot application, communication with octave and using qographics to draw
- templates/ and qoplot.kdevelop - my workshop stuff, which I store here fr my convenience

Build instructions
==================

Requirements:

To build qoplot, you need:
- Qt ver >=4.1 (4.4 for uicontrols) with development tools
- octave >=2.9.9(?) with development tools

Instructions:

Run Qt-4's qmake in main directory. Warning: depending on your distribution,
the qmake for Qt-4 may be called qmake4 or qmake-qt4.

Then run make.

Currentyl there is something messaed up with build order, so you'd have to
build make -k few times to build everything.

How to install
==============


Frankly speaknig - I don't know yet :)
I've ripped off octplot's built/install system, and haven't replaced it with
any alternative.

To run qoplot without installing, just:
- enter the 'out' directory, 
- launch octave,
- run the 'qoplot_enable' command.

Now you're ready to go.

