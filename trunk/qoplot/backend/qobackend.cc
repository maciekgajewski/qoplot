#include <stdio.h>

#include "octave/oct.h"
#include "octave/graphics.h"



class QOBackend : public base_graphics_backend
{
public:
  QOBackend (void)
    : base_graphics_backend ("qoplot") { }

  ~QOBackend (void) { }

  bool is_valid (void) const { return true; }

  void close_figure (const octave_value& ov) const
  {
    printf("qoplot: close figure\n");
  }

  void redraw_figure (const graphics_handle& fh) const
  {
    printf("qoplot: redraw figure\n");
  }

  void print_figure (const graphics_handle& /*fh*/,
		     const std::string& /*term*/,
		     const std::string& /*file*/, bool /*mono*/,
		     const std::string& /*debug_file*/) const
	{
    printf("qoplot: print figure\n");
	}

  Matrix get_canvas_size (const graphics_handle& fh) const
  {
    printf("qoplot: get canvas size\n");
    return Matrix();
  }

  double get_screen_resolution (void) const
  {
    printf("qoplot: get screen resolution\n");
    return 72.0;
  }

  Matrix get_screen_size (void) const
  {
    printf("qoplot: get screen size\n");
    Matrix sz (1, 2, 0.0);
    sz(0) = 100;
    sz(1) = 100;
    return sz;
  }
};

static bool backend_registered = false;
// call this to init the fltk backend
DEFUN_DLD (qobackend, , , "")
{
  graphics_backend::register_backend (new QOBackend);
  backend_registered = true;

  octave_value retval;
  return retval;
}

// EOF
