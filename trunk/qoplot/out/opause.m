function opause(arg)

  octplot_redraw();
  
  if(nargin==0)
    builtin("pause");
  else
    builtin("pause",arg);
  endif
  
endfunction