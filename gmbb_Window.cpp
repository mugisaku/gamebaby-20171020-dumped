#include"gmbb_Window.hpp"
#include<cstdlib>




namespace gmbb{




Window::
Window():
state(WindowState::hidden)
{
}


Window::
Window(Rectangle  rect):
Widget(rect),
width_max(rect.w),
height_max(rect.h),
state(WindowState::full_opened)
{
}




WindowState
Window::
get_state() const
{
  return state;
}


void
Window::
set_state(WindowState  st)
{
  state = st;

    switch(state)
    {
  case(WindowState::hidden):
      break;
  case(WindowState::open_to_down):
      rectangle.w = width_max;
      rectangle.h =         1;
      break;
  case(WindowState::close_to_left):
  case(WindowState::close_to_up):
  case(WindowState::full_opened):
      rectangle.w = width_max;
      rectangle.h = height_max;
      break;
  case(WindowState::open_to_right):
      rectangle.w =          1;
      rectangle.h = height_max;
      break;
    }
}


void
Window::
controll(Controller const&  ctrl) noexcept
{
    if(ctrl.test(down_button_pressed))
    {
      state = WindowState::open_to_down;
    }

  else
    if(ctrl.test(up_button_pressed))
    {
      state = WindowState::close_to_up;
    }


    switch(state)
    {
  case(WindowState::hidden):
  case(WindowState::full_opened):
      break;
  case(WindowState::open_to_right):
        if(rectangle.w < width_max)
        {
          ++rectangle.w;

            if(rectangle.w == width_max)
            {
              state = WindowState::full_opened;
            }
        }
      break;
  case(WindowState::close_to_left):
        if(rectangle.w > 1)
        {
          --rectangle.w;

            if(rectangle.w == 1)
            {
              state = WindowState::hidden;
            }
        }
      break;
  case(WindowState::open_to_down):
        if(rectangle.h < height_max)
        {
          ++rectangle.h;

            if(rectangle.h == height_max)
            {
              state = WindowState::full_opened;
            }
        }
      break;
  case(WindowState::close_to_up):
        if(rectangle.h > 1)
        {
          --rectangle.h;

            if(rectangle.h == 1)
            {
              state = WindowState::hidden;
            }
        }
      break;
    }
}


void
Window::
render(Image&  dst) noexcept
{
    if(rectangle.w < 16){rectangle.w = 16;}
    if(rectangle.h < 16){rectangle.h = 16;}


    if(state != WindowState::hidden)
    {
      dst.draw_frame(rectangle.x,rectangle.y,rectangle.w,rectangle.h);

      dst.draw_line(Line(Point(rectangle.x,rectangle.y),
                         Point(rectangle.x+rectangle.w,rectangle.y+rectangle.h)),Pixel(0700,1));

        if(state == WindowState::full_opened)
        {
//            if(callback)
            {
//              callback(*this,dst);
            }
        }
    }
}


}




