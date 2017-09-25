#include"gmbb_Game_private.hpp"




namespace gmbb{


namespace{


constexpr Point  message_point(8,160);

constexpr uint32_t  key_flags = flags_of_input::p_button;

MessageWindow*
window;


void
operate_message(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

    if(window->is_stopped())
    {
        if(ctrl.test(p_button))
        {
          window->scroll();

          return;
        }
    }


  auto  now = ctrl.get_time();

  constexpr uint32_t  interval_time_base = 200;

  auto  interval_time = interval_time_base;

  static uint32_t  last_time;

    if(ctrl.test(p_button))
    {
      interval_time /= 5;
    }


    if(now > (last_time+interval_time))
    {
      last_time = now;

      window->step();
    }
}




void
process(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

    if((*window == WindowState::open_to_down) ||
       (*window == WindowState::close_to_up ))
    {
      window->animate();
    }

  else
    if((*window == WindowState::full_opened) && is_not_waiting_for(key_flags))
    {
        if(window->is_remaining())
        {
          operate_message(ctrl);
        }

      else
        if(ctrl.test(p_button))
        {
            if(window->is_clean())
            {
              window->set_state(WindowState::close_to_up);
            }

          else
            {
              window->clear();

              wait_until_be_released(key_flags);
            }
        }
    }

  else
    if(*window == WindowState::hidden)
    {
      window->leave_from_parent();

      pop_routine();
    }
}


}


void
start_message(char16_t const*  text) noexcept
{
    if(!window)
    {
      window = new MessageWindow(glset,36,4);
    }


  wait_until_be_released(key_flags);

  window->enter_into(root_widget,message_point);

  window->set_state(WindowState::open_to_down);

  window->push(text);


  push_routine(process);
}


}




