#include"gmbb_Game_private.hpp"




namespace gmbb{


namespace{


MenuWindow*
menu_window;


constexpr int  key_flags = flags_of_input::p_button|flags_of_input::n_button;


covered_ptr<game::SackItem>
item_ptr;


void
operate(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

  static bool  waiting;

    if(waiting)
    {
      auto  r = get_response();

      waiting = false;

        if(r >= 0)
        {
          auto&  hero_p = *board.get_hero_piece();

            switch(r)
            {
          case(0):
              hero_p.change_equipment(item_ptr);
              update_status_monitor();
              update_status_reportor();
              break;
          case(1):
              
              break;
          case(2):
              break;
            }
        }
    }

  else
    if(ctrl.test(p_button))
    {
      auto&  gi = hero.get_sack().get_item(menu_window->get_item_index());

      item_ptr = &gi;

      char16_t const*  fon = gi->get_first_operation_name();


      wait_until_be_released(key_flags);

      start_choosing({fon,u"なげる",u"おく"},Point(40,80));

      waiting = true;
    }

  else
    if(ctrl.test(n_button))
    {
      menu_window->reset_cursor();

      menu_window->leave_from_parent();

      pop_routine();

      wait_until_be_released(key_flags);
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


void
callback(Image&  dst, Point  point, int  i)
{
  Pixel  pixels[] = {Pixel(null),Pixel(white),Pixel(null),Pixel(null)};

  auto&  gi = hero.get_sack().get_item(i);

  dst.print(gi->get_name(),point,glset,pixels);
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
start_sack_menu() noexcept
{
    if(!menu_window)
    {
      Menu  menu(glset.get_width()*20,glset.get_height(),2,8);

      menu_window = new MenuWindow(menu,callback,1);
    }



  wait_until_be_released(key_flags);

  menu_window->enter_into(root_widget,Point(96,24));

  menu_window->set_state(WindowState::open_to_down);

  push_routine(process);
}


}




