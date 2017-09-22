#include"gmbb_Game_private.hpp"




namespace gmbb{


namespace{


MenuWindow*
menu_window;


char16_t const*
table[8];


bool
is_cancelable;


void  process(Controller const&  ctrl) noexcept;


void
operate(Controller const&  ctrl) noexcept
{
    if(ctrl.test(p_button_pressed))
    {
      set_response(menu_window->get_item_index());

      menu_window->leave_from_parent();

      pop_routine(process);
    }

  else
    if(is_cancelable && ctrl.test(n_button_pressed))
    {
      set_response(-1);

      menu_window->leave_from_parent();

      pop_routine(process);
    }

  else if(ctrl.test(up_button_pressed)   ){menu_window->move_cursor_to_up();}
  else if(ctrl.test(down_button_pressed) ){menu_window->move_cursor_to_down();}
}


void
callback(Image&  dst, Point  point, int  i) noexcept
{
  Pixel  pixels[] = {Pixel(null),Pixel(white),Pixel(null),Pixel(null)};

  dst.print(table[i],point,glset,pixels);
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
    if(*menu_window == WindowState::full_opened)
    {
      operate(ctrl);
    }

  else
    if(*menu_window == WindowState::hidden)
    {
      menu_window->leave_from_parent();

      pop_routine(process);
    }
}


}


void
start_choosing(std::initializer_list<char16_t const*>  ls, Point  point, bool  cancelable) noexcept
{
    if(!menu_window)
    {
      Menu  menu(glset.get_width()*5,glset.get_height(),1,8);

      menu_window = new MenuWindow(menu,callback);

      menu_window->lock_base();
    }


  menu_window->change_visible_row_number(ls.size());

  auto  it = ls.begin();

    for(auto&  e: table)
    {
      e = *it++;
    }


  menu_window->enter_into(root_widget,point);

  menu_window->set_state(WindowState::open_to_down);

  is_cancelable = cancelable;

  push_routine(process);
}


}




