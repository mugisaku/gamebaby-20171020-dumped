#include"gmbb_Game_private.hpp"




namespace gmbb{


namespace{


constexpr Point  message_point(8,160);

MessageWindow*
window;


void
operate_message(Controller const&  ctrl) noexcept
{
  static bool  pressing;

    if(ctrl.test(p_button_pressed))
    {
      pressing = true;
    }


    if(window->is_stopped())
    {
        if(pressing)
        {
          window->scroll();

          return;
        }
    }


    if(ctrl.test(p_button_released))
    {
      pressing = false;
    }


  auto  now = ctrl.get_time();

  constexpr uint32_t  interval_time_base = 200;

  auto  interval_time = interval_time_base;

  static uint32_t  last_time;

    if(pressing)
    {
      interval_time /= 5;
    }


    if(now > (last_time+interval_time))
    {
      last_time = now;

      window->step();
    }
}


}




void
process_message(Controller const&  ctrl) noexcept
{
    if((*window == WindowState::open_to_down) ||
       (*window == WindowState::close_to_up ))
    {
      window->animate();
    }

  else
    if(*window == WindowState::full_opened)
    {
        if(window->is_remaining())
        {
          operate_message(ctrl);
        }

      else
        if(ctrl.test(p_button_pressed))
        {
            if(window->is_clean())
            {
              window->set_state(WindowState::close_to_up);
            }

          else
            {
              window->clear();
            }
        }

      else
        if(ctrl.test(p_button_released))
        {
          window->clear();
        }
    }

  else
    if(*window == WindowState::hidden)
    {
      window->leave_from_parent();
    }
}


bool
is_message_active() noexcept
{
  return window && window->get_parent();
}


void
start_message(char16_t const*  text) noexcept
{
    if(!window)
    {
      window = new MessageWindow(glset,36,4);
    }


  window->enter_into(root_widget,message_point);

  window->set_state(WindowState::open_to_down);

  window->push(text);
}


}




