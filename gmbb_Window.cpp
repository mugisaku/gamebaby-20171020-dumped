#include"gmbb_Window.hpp"
#include<cstdlib>




namespace gmbb{




void
Window::
resize(int  w, int  h) noexcept
{
  width_max  = w;
  height_max = h;

  set_state(WindowState::full_opened);
}


void
Window::
set_state(WindowState  st) noexcept
{
  state = st;

    switch(state)
    {
  case(WindowState::hidden):
      break;
  case(WindowState::open_to_down):
      rectangle.w = width_max;
      rectangle.h =        16;
      break;
  case(WindowState::close_to_left):
  case(WindowState::close_to_up):
  case(WindowState::full_opened):
      rectangle.w = width_max;
      rectangle.h = height_max;
      break;
  case(WindowState::open_to_right):
      rectangle.w =         16;
      rectangle.h = height_max;
      break;
    }


  notify_flag(needing_to_redraw);
}




void
Window::
change_border0_color(ColorIndex  ci) noexcept
{
  pixels[2] = ci;

  notify_flag(needing_to_redraw);
}


void
Window::
change_border1_color(ColorIndex  ci) noexcept
{
  pixels[2] = ci;

  notify_flag(needing_to_redraw);
}


void
Window::
change_surface_color(ColorIndex  ci) noexcept
{
  pixels[1] = ci;

  notify_flag(needing_to_redraw);
}




void
Window::
animate() noexcept
{
  constexpr int  step = 8;

    switch(state)
    {
  case(WindowState::hidden):
  case(WindowState::full_opened):
      break;
  case(WindowState::open_to_right):
        if(rectangle.w < width_max)
        {
          rectangle.w += step;

            if(rectangle.w >= width_max)
            {
              rectangle.w = width_max;

              state = WindowState::full_opened;
            }


          notify_flag(needing_to_redraw);
        }
      break;
  case(WindowState::close_to_left):
        if(rectangle.w > 16)
        {
          rectangle.w -= step;

            if(rectangle.w <= 16)
            {
              rectangle.w = 16;

              state = WindowState::hidden;
            }


          notify_flag(needing_to_redraw);
        }
      break;
  case(WindowState::open_to_down):
        if(rectangle.h < height_max)
        {
          rectangle.h += step;

            if(rectangle.h >= height_max)
            {
              rectangle.h = height_max;

              state = WindowState::full_opened;
            }


          notify_flag(needing_to_redraw);
        }
      break;
  case(WindowState::close_to_up):
        if(rectangle.h > 16)
        {
          rectangle.h -= step;

            if(rectangle.h <= 16)
            {
              rectangle.h = 16;

              state = WindowState::hidden;
            }


          notify_flag(needing_to_redraw);
        }
      break;
    }
}


void
Window::
render(Image&  dst) noexcept
{
    if(state != WindowState::hidden)
    {
      draw_frame(dst);

      Widget::render(dst);
    }
}


}




