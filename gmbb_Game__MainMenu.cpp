#include"gmbb_Game_private.hpp"




namespace gmbb{


namespace{


MenuWindow*
menu_window;


constexpr uint32_t  key_flags = (flags_of_input::p_button|flags_of_input::n_button);


void  process(Controller const&  ctrl) noexcept;


void
operate(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

  constexpr int        talk = 0;
  constexpr int  belongings = 1;
  constexpr int        foot = 2;
  constexpr int   interrupt = 3;

    if(ctrl.test(p_button))
    {
        switch(menu_window->get_item_index())
        {
      case(talk):
          menu_window->reset_cursor();

          menu_window->leave_from_parent();

          pop_routine();

          hide_status_reportor();

          start_message(u"その　ほうこうには　だれもいない");
          break;
      case(belongings):
          start_sack_menu();
          break;
      case(foot):
          break;
      case(interrupt):
          break;
      default:;
          break;
        }
    }

  else
    if(ctrl.test(n_button))
    {
      menu_window->reset_cursor();

      menu_window->leave_from_parent();

      pop_routine();


      hide_status_reportor();

      wait_until_be_released(key_flags);
    }

  else if(ctrl.test(up_button)   ){menu_window->move_cursor_to_up();}
  else if(ctrl.test(down_button) ){menu_window->move_cursor_to_down();}
  else if(ctrl.test(left_button) ){menu_window->move_cursor_to_left();}
  else if(ctrl.test(right_button)){menu_window->move_cursor_to_right();}
}


void
process(Controller const&  ctrl) noexcept
{
    if((*menu_window == WindowState::open_to_down) ||
       (*menu_window == WindowState::close_to_up))
    {
      menu_window->animate();
    }

  else
    if((*menu_window == WindowState::full_opened) &&
       is_not_waiting_for(key_flags))
    {
      operate(ctrl);
    }
}


}


void
start_main_menu() noexcept
{
    if(!menu_window)
    {
      Menu  menu(glset.get_width()*5,glset.get_height(),2,2);

      menu_window = new MenuWindow(menu,[](Image&  dst, Point  point, int  i)
        {
          Pixel  pixels[] = {Pixel(null),Pixel(white),Pixel(null),Pixel(null)};

          static char16_t const*  text_table[] = {
            u"はなす",u"もちもの",
            u"あしもと",u"ちゅうだん",
          };


          dst.print(text_table[i],point,glset,pixels);
        });
    }


  wait_until_be_released(key_flags);

  menu_window->enter_into(root_widget,Point(8,24));

  menu_window->set_state(WindowState::open_to_down);

  show_status_reportor();

  push_routine(process);
}


}




