## Copyright (C) 2005 Shai Ayal
## Adapted to QOPlot in 2008 by Maciek Gajewski <maciej.gajewski0@gmail.com>
##
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2, or (at your option)
## any later version.
##
## OctPlot is distributed in the hope that it will be useful, but
## WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
## General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with OctPlot; see the file COPYING.  If not, write to the Free
## Software Foundation, 59 Temple Place - Suite 330, Boston, MA
## 02111-1307, USA.

## -*- texinfo -*-
## @deftypefn {Function File} octplot_enable
## This script enables octplot operation. 
## @end deftypefn
## @seealso{set,get,plot,hold}

## Author: shaia

## this needs a newer version of dispatch

if( ~exist("qoplot_config_info","var"))
  global qoplot_config_info
  qoplot_config_info.mpath = \
       	"/usr/libexec/octave/2.9.9/site/qoplot-0.4.0";
  qoplot_config_info.opath = \
       "/usr/libexec/octave/2.9.9/site/qoplot-0.4.0";
  qoplot_config_info.version = \
       	"0.4.0";
  qoplot_config_info.in_use = 0;
  qoplot_config_info.clear_command = "clear ";
  qoplot_tmp1 = glob (sprintf ("%s/*.m", qoplot_config_info.mpath));

  # Removed. Will be intorduced once sane build system is in place
  #if(strcmp(version(),"2.9.9")==0)
  #  error("Octplot was compiled for a different version of Octave");
  #endif

  if(isempty(qoplot_tmp1))
    % running inside the distribution directory
    qoplot_tmp1 = glob ("*.m");
  endif
  for qoplot_tmp2 = 1 : length (qoplot_tmp1)
    qoplot_config_info.clear_command = \
      sprintf ("%s %s", \
        qoplot_config_info.clear_command, \
        split (split (qoplot_tmp1 {qoplot_tmp2}, "/") (end, :), ".") (1, :));
  endfor
endif


  eval (qoplot_config_info.clear_command);

  dispatch("pause","opause","any");
  dispatch("set","oset","any");
  dispatch("get","oget","any");
  dispatch("hold","ohold","any");
  dispatch("gset","gnuplot_warn","any");
  dispatch("graw","gnuplot_warn","any");
  dispatch("oneplot","gnuplot_warn","any");
  dispatch("clg","gnuplot_warn","any");
  
  ## set some function as commands (not needing ())
  mark_as_command hold
  mark_as_command clf
  mark_as_command cla
  mark_as_command gca
  mark_as_command gcf
  mark_as_command figure
  mark_as_command grid
  mark_as_command print
  mark_as_command box
  mark_as_command shading 
 
  ## lock all important functions
  mlock("qoplot_redraw");
  mlock("qoplot_command");
  mlock("qoplot_atexit");
  
  ## redraw at prompt if needed
  input_event_hook("qoplot_redraw");
  ## kill at octave exit
  atexit("qoplot_atexit");
  
  qoplot_config_info.in_use = 1;

  ## special for running inside the distribution directory
  [s, err, msg] = stat("./qoplot_dist_dir.txt");
  if (err==0)
    qoplot_path("./qoplot");
    #set(0,"DefaultFontDir","../fonts/"); TODO is this needed?
    addpath("../high_level");
  else
    addpath(qoplot_config_info.mpath);
    addpath(qoplot_config_info.opath);
    eval (qoplot_config_info.clear_command);
  endif


global __qoplot__print_once__ = 1;
## if we are in quite mode, stay quiet!
if( length(argv()) && sum(cellfun(@(x) strcmp(x,"-q"),argv())) )
  __qoplot__print_once__ = 0;
endif

if(__qoplot__print_once__)
  __qoplot__print_once__ = 0;
  printf("\n\
Octplot 0.4.0 Copyright (C) 2003-2007 By Shai Ayal.\n\
QOPlot version %s Copyright (C) 2008 by Maciek Gajewski.\n\
\n\
This program is free software; you can redistribute it and/or modify it\n\
under the terms of the GNU General Public License as published by\n\
the Free Software Foundation; either version 2, or (at your option)\n\
any later version.\n\
\n\
Bugs goes there: http://code.google.com/p/qoplot/\n\
\n\
For general help, type \"help qoplot\"\n\n",
qoplot_config_info.version);
endif	  	 

 	  	 
