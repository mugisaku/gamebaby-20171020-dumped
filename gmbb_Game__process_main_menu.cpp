#include"gmbb_Game_private.hpp"




namespace gmbb{


namespace{


MenuWindow*
menu_window;


void
operate_main_menu(Controller const&  ctrl) noexcept
{
  constexpr int        talk = 0;
  constexpr int  belongings = 1;
  constexpr int        foot = 2;
  constexpr int   interrupt = 3;
  constexpr int   undecided = -1;

  static int  current = undecided;

    if(ctrl.test(p_button_pressed))
    {
      current = menu_window->get_item_index();

        switch(current)
        {
      case(talk):
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
    if(ctrl.test(n_button_pressed))
    {
      menu_window->reset_cursor();

      menu_window->set_state(WindowState::close_to_up);

      current = undecided;
    }

  else if(ctrl.test(up_button_pressed)   ){menu_window->move_cursor_to_up();}
  else if(ctrl.test(down_button_pressed) ){menu_window->move_cursor_to_down();}
  else if(ctrl.test(left_button_pressed) ){menu_window->move_cursor_to_left();}
  else if(ctrl.test(right_button_pressed)){menu_window->move_cursor_to_right();}
}


}


void
process_main_menu(Controller const&  ctrl) noexcept
{
    if((*menu_window == WindowState::open_to_down) ||
       (*menu_window == WindowState::close_to_up))
    {
      menu_window->animate();
    }

  else
    if(*menu_window == WindowState::full_opened)
    {
      operate_main_menu(ctrl);
    }

  else
    if(*menu_window == WindowState::hidden)
    {
      menu_window->leave_from_parent();
    }
}


bool
is_main_menu_active() noexcept
{
  return menu_window && menu_window->get_parent();
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


  menu_window->enter_into(root_widget,Point(8,24));

  menu_window->set_state(WindowState::open_to_down);
}


}




