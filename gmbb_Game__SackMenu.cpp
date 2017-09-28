#include"gmbb_Game_private.hpp"




namespace gmbb{


namespace{


ColumnStyleMenuWindow*
menu_window;


covered_ptr<game::SackItem>
item_ptr;


void
callback(Image&  dst, Point  point, int  i)
{
  auto&  gi = hero.get_sack().get_item(i);

    if(gi)
    {
        if(gi.is_equipped())
        {
          dst.print(u'E',point,glset);
        }


      point.x += glset.get_width();

        if(gi.is_cursed())
        {
          dst.print(u'C',point,glset);
        }


      point.x += glset.get_width();

      dst.print(gi->get_name(),point,glset);
    }
}


void
return_(int  retval) noexcept
{
  constexpr int  top    = 0;
  constexpr int  throw_ = 1;
  constexpr int  put    = 2;

    if(retval >= 0)
    {
      auto&  hero_p = *board.get_hero_piece();

        switch(retval)
        {
      case(top):
          hero_p.hold_item(item_ptr);
          break;
      case(throw_):
          hero_p.unhold_item(item_ptr);
          break;
      case(put):
          auto&  sq = *hero_p.get_square();

            if(sq.can_put_item())
            {
              sq.set_item(*item_ptr);

              hero_p.unhold_item(item_ptr);
            }

          else
            {
            }

          break;
        }


      hero.get_sack().sort();

      update_status_monitor();
      update_status_reportor();
    }


  close_choosing_window();
}


void
process(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

    if(ctrl.test(p_button))
    {
      auto&  gi = hero.get_sack().get_item(menu_window->get_item_index());

        if(gi)
        {
          item_ptr = &gi;

          char16_t const*  fon = gi->get_first_operation_name();


          prepare_choosing_window({fon,u"なげる",u"おく"},Point(40,80));

          start_choosing();
        }
    }

  else
    if(ctrl.test(n_button))
    {
      pop_routine();
    }

  else
    if(interval_timer.check(200,ctrl.get_time()))
    {
           if(ctrl.test(up_button)   ){menu_window->move_cursor_to_up();  interval_timer.enable();}
      else if(ctrl.test(down_button) ){menu_window->move_cursor_to_down();  interval_timer.enable();}
      else if(ctrl.test(left_button) ){menu_window->move_cursor_to_left();  interval_timer.enable();}
      else if(ctrl.test(right_button)){menu_window->move_cursor_to_right();  interval_timer.enable();}
      else {interval_timer.disable();}
    }
}


}


void
open_sack_menu_window() noexcept
{
    if(!menu_window)
    {
      Menu  menu(glset.get_width()*20,glset.get_height(),8,callback);

      menu_window = new ColumnStyleMenuWindow(menu,2);
    }



  menu_window->enter_into(root_widget,Point(96,24));

  menu_window->set_state(WindowState::full_opened);
}


void
close_sack_menu_window() noexcept
{
  menu_window->reset_cursor();

  menu_window->leave_from_parent();

  menu_window->set_state(WindowState::hidden);
}


void
start_sack_menu() noexcept
{
  open_sack_menu_window();

  push_routine(process,return_);
}


}




