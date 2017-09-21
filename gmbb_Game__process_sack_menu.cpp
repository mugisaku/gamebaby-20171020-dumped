#include"gmbb_Game_private.hpp"




namespace gmbb{


namespace{


MenuWindow*
menu_window;


int
phase;


void
operate(Controller const&  ctrl) noexcept
{
    if(phase == 1)
    {
    }

  else
    if(ctrl.test(p_button_pressed))
    {
      phase = 1;

      menu_window->get_item_index();

      start_choosing({u"そうび",u"なげる",u"おく"},Point(40,80));
    }

  else
    if(ctrl.test(n_button_pressed))
    {
      menu_window->reset_cursor();

      menu_window->set_state(WindowState::close_to_up);
    }

  else if(ctrl.test(up_button_pressed)   ){menu_window->move_cursor_to_up();}
  else if(ctrl.test(down_button_pressed) ){menu_window->move_cursor_to_down();}
  else if(ctrl.test(left_button_pressed) ){menu_window->move_cursor_to_left();}
  else if(ctrl.test(right_button_pressed)){menu_window->move_cursor_to_right();}
}


void
callback(Image&  dst, Point  point, int  i)
{
  Pixel  pixels[] = {Pixel(null),Pixel(white),Pixel(null),Pixel(null)};

  auto&  gi = *hero.get_sack().item_table[i].pointer;

  dst.print(gi.get_name(),point,glset,pixels);
}


}


void
process_sack_menu(Controller const&  ctrl) noexcept
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
    }
}


bool
is_sack_menu_active() noexcept
{
  return menu_window && menu_window->get_parent();
}


void
start_sack_menu() noexcept
{
    if(!menu_window)
    {
      Menu  menu(glset.get_width()*20,glset.get_height(),2,8);

      menu_window = new MenuWindow(menu,callback,1);
    }


  menu_window->enter_into(root_widget,Point(96,24));

  menu_window->set_state(WindowState::open_to_down);

  phase = 0;
}


}




