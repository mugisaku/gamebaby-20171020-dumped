#include"gmbb_Game_private.hpp"




namespace gmbb{


namespace{


ColumnStyleMenuWindow*
menu_window;


char16_t const*
table[8];


Point
window_point;


bool
is_cancelable;


void
process(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

    if(ctrl.test(p_button))
    {
      pop_routine(menu_window->get_item_index());
    }

  else
    if(is_cancelable && ctrl.test(n_button))
    {
      pop_routine(-1);
    }

  else
    if(interval_timer.check(200,ctrl.get_time()))
    {
           if(ctrl.test(up_button)  ){  menu_window->move_cursor_to_up();  interval_timer.enable();}
      else if(ctrl.test(down_button)){  menu_window->move_cursor_to_down();  interval_timer.enable();}
      else {interval_timer.disable();}
    }
}


void
callback(Image&  dst, Point  point, int  i) noexcept
{
  dst.print(table[i],point,glset);
}


void
create_window() noexcept
{
    if(!menu_window)
    {
      Menu  menu(glset.get_width()*5,glset.get_height(),0,callback);

      menu_window = new ColumnStyleMenuWindow(menu);
    }
}


}


void
prepare_choosing_window(std::initializer_list<char16_t const*>  ls, Point  point) noexcept
{
  create_window();


  menu_window->change_row_number(ls.size());

  auto  it = ls.begin();

    for(auto&  e: table)
    {
      e = *it++;
    }


  window_point = point;
}


void
open_choosing_window() noexcept
{
  create_window();

  menu_window->enter_into(root_widget,window_point);

  menu_window->set_state(WindowState::full_opened);
}


void
close_choosing_window() noexcept
{
  menu_window->leave_from_parent();
}


void
start_choosing(bool  cancelable) noexcept
{
  open_choosing_window();

  is_cancelable = cancelable;

  push_routine(process);
}


}




