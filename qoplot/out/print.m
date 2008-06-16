## Copyright (C) 2003 Shai Ayal
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
##
## Copyright (C) 2001 Laurent Mazet
## Copyright (C) 1999 Daniel Heiserer

## -*- texinfo -*-
## @deftypefn {Function File} print(@var{args})
## saves the current figure to a file in a variety of formats
## @var{options}:
## @table @code
## @item @var{filename}
##   Output filename
## @item -d@var{format}
##   Output format, where @var{format} is one of:
##   @table @code
##   @item ps
##   @itemx ps2
##   @itemx psc
##   @itemx psc2
##     Postscript (V)
##   @item eps
##   @itemx eps2
##   @itemx epsc
##   @itemx epsc2
##     Encapsulated postscript (V)
##   @item pdf
##     PDF (V)
##   @item jpg
##     JPEG (B)
##   @item png
##     PNG (B)
##   @end table
##
##  (V) denotes a vector format, (B) denotes a bitmap format
## @item -r@var{resolution}
##   resolution for bitmap formats in dpi (default resolution 150 dpi)
## @end table
## 
## The filename and options can be given in any order.
##
## If you are using Octave 2.1.x or above, command("print") will change 
## print from a function to a command, so instead of typing 
## print("-r300","-dpng", "out.png") you can type print -r300 -dpng out.png
##
## @end deftypefn
## @seealso{gcf}

## Author: Shai Ayal <shaiay@users.sourceforge.net>
## some code from the print function from octave-forge written by
## Daniel Heiserer, Laurent Mazet, Paul Kienzle
## Keywords: octplot graphics
function print(varargin)
  
  ## default resolution for bitmaps
  res = "-r150";
  ## default output device -- native to octplot
  device = "epsc2";
  ## default output name
  fname="octplot_hardcopy";
  _op_fmt = 0;
  
  for i=1:nargin
    arg = varargin{i};
    if isstr(arg)
      if(length(arg>2))
        if(arg(1:2) == "-r")
          res = arg;
        elseif(arg(1:2) == "-d")
          device=arg(3:end);
        elseif(length(arg))
          fname=arg;
        else
          error("print: unknown option %s",arg);
        endif
      else
        error("print: unknown option %s",arg);
      endif
    else
      error("print: expecting string arguments");
    endif
  endfor
      
  ## direct octplot printing
  if( ~isempty(findstr("ps",device)))
    if( isempty(findstr("eps",device)))
      _op_fmt = 1;
    endif
    octplot_command("print",fname,_op_fmt);
  else
    ## we need ghostscript for these filetypes, so find it. The output args
    ## if the system function have changed from version 2.1.x to 2.9.x
    ## so we must check for that
    [a,b] = system("which \\gs");
    if(isstr(a))
      gs = a;
    else
      gs = b;
    endif
    ## strip all non-printing chars (mainly cr/lf)
    gs = gs(gs>=" ");
    if( ~exist(gs,"file"))
      error("Printing to this format requires ghostscript");
    endif
    gs_commandline=sprintf("%s -dEPSCrop -q -dSAFER -dBATCH -dNOPAUSE %s ",gs,res);
    fn=tmpnam();
    octplot_command("print",fn,0);
    
    if( strcmp(device,"pdf") )
      system(sprintf("%s -sDEVICE=pdfwrite -sOutputFile=%s %s",\
                      gs_commandline , fname, fn));
    elseif( strcmp(device,"png") )
      system(sprintf("%s  -dTextAlphaBits=4 -sDEVICE=png16m -sOutputFile=%s %s",\
                      gs_commandline , fname, fn));
    elseif( strcmp(device,"jpg") )
      system(sprintf("%s  -dTextAlphaBits=4 -sDEVICE=jpeg -sOutputFile=%s %s",\
                      gs_commandline , fname, fn));
    else
      error("Unknown output format %s",device);
    endif
    
    unlink(fn);
  endif
endfunction
