function opause(arg)

  % MACIEK: is this still needed?
  %qoplot_redraw();
  
  if(nargin==0)
    builtin("pause");
  else
    builtin("pause",arg);
  endif
  
endfunction