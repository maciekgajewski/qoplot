## Copyright (C) 2006 Michel D. Schmid
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


## Author: mds mailto:michaelschmid@users.sourceforge.net
## $Revision$, $Date$

function test_stem

  # set protocol file name
  rowDate = clock();
  strDiaryFileName = [num2str(rowDate(1)) "-" num2str(rowDate(2)) "-" num2str(rowDate(3)) "-" \
	                    num2str(rowDate(4)) "-" num2str(rowDate(5)) "-" num2str(rowDate(6)) \
											"-stem_test-protocol.txt"];

  diary(strDiaryFileName) # starts the diary into file

	# test stem plots
	disp("Test 1:")
	try # test 1
	  x = 1:10;
	  stem(x);
	  disp("Passed")
	catch
	  disp("Failed: x = 1:10; stem(x)");
	  disp(lasterr);
	end_try_catch
	
	disp("Test 2:")
	try # test 2
	  x = 1:10;
	  h = stem(x);
	  disp("Passed: x = 1:10; h = stem(x)")
	catch
	  disp("Failed: x = 1:10; h = stem(x)");
	  disp(lasterr);
	end_try_catch

	disp("Test 3:")
	try # test 3
	  y = -2.9:0.2:2.9;
	  h = stem(1:length(y),y);
	  disp("Passed: x = -2.9:0.2:2.9; h = stem(1:length(y),y);")
	catch
	  disp("Failed: x = -2.9:0.2:2.9; h = stem(1:length(y),y);");
	  disp(lasterr);
	end_try_catch
	
	disp("Test 4:")
	try # test 4
	  y = -2.9:0.2:2.9;
	  h = stem(1:length(y),y,"fill");
	  disp("Passed: x = -2.9:0.2:2.9; h = stem(1:length(y),y,""fill"");")
	catch
	  disp("Failed: x = -2.9:0.2:2.9; h = stem(1:length(y),y,""fill"");");
	  disp(lasterr);
	end_try_catch
	
	disp("Test 5:")
	try # test 5
	  y = -2.9:0.2:2.9;
	  h = stem(1:length(y),y,"fill","m");
	  disp("Passed: x = -2.9:0.2:2.9; h = stem(1:length(y),y,""fill"",""m"");")
	catch
	  disp("Failed: x = -2.9:0.2:2.9; h = stem(1:length(y),y,""fill"",""m"");");
	  disp(lasterr);
	end_try_catch
	
	disp("Test 6:")
	try # test 6
	  y = -2.9:0.2:2.9;
	  h = stem(1:length(y),y,"fill",":md") ;
	  disp("Passed: x = -2.9:0.2:2.9; h = stem(1:length(y),y,""fill"","":md"");")
	catch
	  disp("Failed: x = -2.9:0.2:2.9; h = stem(1:length(y),y,""fill"","":md"");");
	  disp(lasterr);
	end_try_catch
	
	disp("Test 7:")
	try # test 7
	  y = -2.9:0.2:2.9;
	  h = stem(1:length(y),y,":mv","fill") ;
	  disp("Passed: x = -2.9:0.2:2.9; h = stem(1:length(y),y,"":mv"",""fill"");")
	catch
	  disp("Failed: x = -2.9:0.2:2.9; h = stem(1:length(y),y,"":mv"",""fill"");");
	  disp(lasterr);
	end_try_catch

	diary off
  

endfunction

