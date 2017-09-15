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
  WindowState  state;

  int   width_max;
  int  height_max;

public:
  Window();
  Window(Rectangle  rect);

  WindowState  get_state() const;
  void  set_state(WindowState  st);

  void  controll(Controller const&  ctrl) noexcept override;

  void  render(Image&  dst) noexcept override;

};


}




#endif




