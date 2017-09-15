#ifndef GMBB_WINDOW_HPP
#define GMBB_WINDOW_HPP


#include"gmbb_Widget.hpp"


namespace gmbb{


enum class
WindowState
{
  hidden,

  full_opened,

  open_to_down,
  open_to_right,
  close_to_up,
  close_to_left,

};


class
Window: public Widget
{
protected:
  WindowState  state;

  Pixel  pixels[4] = {Pixel(predefined_color_index::null),
                      Pixel(predefined_color_index::blue),
                      Pixel(predefined_color_index::white),
                      Pixel(predefined_color_index::light_gray)};

  int   width_max=0;
  int  height_max=0;

  void  draw_frame(Image&  dst) const noexcept;

public:
  Window();
  Window(int  w, int  h);

  WindowState  get_state() const noexcept{return state;}
  void  set_state(WindowState  st) noexcept;

  void  change_border0_color(ColorIndex  ci) noexcept;
  void  change_border1_color(ColorIndex  ci) noexcept;
  void  change_surface_color(ColorIndex  ci) noexcept;

  void  controll(Controller const&  ctrl) noexcept override;

  void  render(Image&  dst) noexcept override;

};


}




#endif




