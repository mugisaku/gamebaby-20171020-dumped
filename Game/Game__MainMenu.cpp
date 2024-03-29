#include"Game_private.hpp"
#include"EventQueue.hpp"




namespace gmbb{


namespace{


constexpr int        talk = 0;
constexpr int  belongings = 1;
constexpr int        foot = 2;
constexpr int   interrupt = 3;


ScrollStyleMenuWindow*
menu_window;


covered_ptr<GameItem>
empty;


void
return_(int  retval) noexcept
{
  constexpr Point  point(80,80);

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
    {
        if(empty && (retval == 0))
        {
          auto&  sq = *hero_piece->get_square();

          auto&  item = sq.get_item();
          auto&  trap = sq.get_trap();

            if(item)
            {
              *empty = item             ;
                       item = GameItem();

              pop_routine();
            }

          else
            if(trap)
            {
              pop_routine();
            }
        }


      close_message_window();
   }
      break;
  case(interrupt):
      break;
  default:;
      break;
    }
}


covered_ptr<Piece>
get_talk_target() noexcept
{
  auto  sq = hero_piece->get_square();

  auto  target_sq = sq->get_linked_square(hero_piece->get_direction());

  return target_sq? target_sq->get_piece():nullptr;
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
        {
          auto  target = get_talk_target();

            if(target)
            {
              event_queue::push(PieceEvent{PieceEventKind::talk,hero_piece,target});
            }

          else
            {
              event_queue::push(MessageEvent{"その　ほうこうには　だれもいない"});
            }
        }
          break;
      case(belongings):
          start_sack_menu();
          break;
      case(foot):
        {
          auto&  sq = *hero_piece->get_square();

          auto&  item = sq.get_item();
          auto&  trap = sq.get_trap();

            if(item)
            {
              char  buf[256];

              empty = hero.get_sack().find_empty();

              snprintf(buf,sizeof(buf),"%s　がおちている",item->get_name());

                if(empty)
                {
                  start_message_with_choosing(buf,{"ひろう","ひろわない"});
                }

              else
                {
                  start_message(buf);
                }
            }

          else
            if(trap)
            {
              char  buf[256];

              empty = hero.get_sack().find_empty();

              snprintf(buf,sizeof(buf),"%sのワナ　がある",trap.get_name());

                if(empty)
                {
                  start_message_with_choosing(buf,{"さどうさせる","とりはずす","はかいする"});
                }

              else
                {
                  start_message(buf);
                }
            }

          else
            {
              start_message("あしもとには　なにもない");
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


      menu_window = new ScrollStyleMenuWindow(menu,2,2,Point(8,24));

      menu_window->set_name("main menu window");
    }


  task_list::push(*menu_window);

  menu_window->set_state(WindowState::full_opened);
}


void
close_main_menu_window() noexcept
{
  menu_window->reset_cursor();

  task_list::erase(*menu_window);
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




