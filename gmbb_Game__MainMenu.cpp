#include"gmbb_Game_private.hpp"




namespace gmbb{


namespace{


constexpr int        talk = 0;
constexpr int  belongings = 1;
constexpr int        foot = 2;
constexpr int   interrupt = 3;


ScrollStyleMenuWindow*
menu_window;


void
return_(int  retval) noexcept
{
    switch(menu_window->get_item_index())
    {
  case(talk):
      close_message_window();
      break;
  case(belongings):
      close_sack_menu_window();

        if(retval < 0)
        {
          pop_routine();
        }
      break;
  case(foot):
      close_message_window();
      break;
  case(interrupt):
      break;
  default:;
      break;
    }
}


void
process(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

    if(ctrl.test(p_button))
    {
        switch(menu_window->get_item_index())
        {
      case(talk):
          start_message(u"その　ほうこうには　だれもいない");
          break;
      case(belongings):
          start_sack_menu();
          break;
      case(foot):
        {
          auto&  sq = *hero_piece->get_square();

          auto   item = sq.get_item();
          auto&  trap = sq.get_trap();

            if(item)
            {
              std::u16string  s(item->get_name());

              s += u"　がおちている";


              start_message(s.data());
            }

          else
            if(trap)
            {
              std::u16string  s(u"ワナがある");

              start_message(s.data());
            }

          else
            {
              start_message(u"あしもとには　なにもない");
            }
        }
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
      pop_routine();
    }

  else if(ctrl.test(up_button)   ){menu_window->move_cursor_to_up();}
  else if(ctrl.test(down_button) ){menu_window->move_cursor_to_down();}
  else if(ctrl.test(left_button) ){menu_window->move_cursor_to_left();}
  else if(ctrl.test(right_button)){menu_window->move_cursor_to_right();}
}


}


void
open_main_menu_window() noexcept
{
    if(!menu_window)
    {
      Menu  menu(glset.get_width()*5,glset.get_height(),2,[](Image&  dst, Point  point, int  i)
        {
          static char16_t const*  text_table[] = {
            u"はなす",u"もちもの",
            u"あしもと",u"ちゅうだん",
          };


          dst.print(text_table[i],point,glset);
        });


      menu_window = new ScrollStyleMenuWindow(menu,2,2);
    }


  menu_window->enter_into(root_widget,Point(8,24));

  menu_window->set_state(WindowState::full_opened);
}


void
close_main_menu_window() noexcept
{
  menu_window->reset_cursor();

  menu_window->leave_from_parent();
}


bool
is_main_menu_window_opened() noexcept
{
  return *menu_window == WindowState::full_opened;
}


void
start_main_menu() noexcept
{
  open_main_menu_window();

  push_routine(process,return_);
}


}




