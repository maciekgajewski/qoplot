Qt-based octave plotter.

# What's this #

Currently this is project to create nice, Qt-based graphics backend for octave, using newest octave gaphics subsytem.

Project started as stand-alone plotter. It was based on [octplot](http://octplot.sourceforge.net/). Like octplot (and unlike gnuplot) - it emulates Matlab's(TM) Handle
Graphics(TM). Unlike octplot, uses Qt and all it's features.

I write this because I need plotting system able to drawing images and basic
plots, and I find UI controls on plot figures useful.

I'm working om image recognition algorithms, and support for displaying and creating images is essential for my work.

## Screenshot ##
First screenshot  - plot already looks like plot.

![http://qoplot.googlecode.com/files/qobackend-1st%20screenshot.png](http://qoplot.googlecode.com/files/qobackend-1st%20screenshot.png)

```
octave:1> qobackend
octave:2> x = [-1:0.1:2];
octave:3> plot( x, sin(x), "r:o")
octave:4> text(0,0,"<-zero", "Color", "b", "FontWeight", "bold");
```