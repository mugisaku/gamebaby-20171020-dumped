#include"gmbb_ScrollStyleMenuWindow.hpp"
#include"gmbb_environment.hpp"




namespace gmbb{


ScrollStyleMenuWindow::
ScrollStyleMenuWindow(Menu const&  menu_, int  col_n, int  row_n) noexcept:
menu(menu_),
column_number(col_n),
row_number(row_n)
{
  Window::resize(menu.get_item_width()*column_number+16,
                 menu.get_image_height()            +16);
}




void
ScrollStyleMenuWindow::
reset_cursor() noexcept
{
  y_base = 0;

  offset = Point();
}




void
ScrollStyleMenuWindow::
move_cursor_to_left()  noexcept
{
    if(offset.x)
    {
      offset.x -= 1;

      notify_flag(needing_to_redraw);
    }
}


void
ScrollStyleMenuWindow::
move_cursor_to_right() noexcept
{
   if(offset.x < (column_number-1))
   {
     offset.x += 1;

     notify_flag(needing_to_redraw);
   }
}


void
ScrollStyleMenuWindow::
move_cursor_to_up()    noexcept
{
       if(offset.y){offset.y -= 1;}
  else if(  y_base){y_base   -= 1;}

  notify_flag(needing_to_redraw);
}


void
ScrollStyleMenuWindow::
move_cursor_to_down()  noexcept
{
       if(                      offset.y < (menu.get_row_number()-1)){offset.y += 1;}
  else if((y_base+menu.get_row_number()) < (         row_number  -1)){y_base   += 1;}

  notify_flag(needing_to_redraw);
}




void
ScrollStyleMenuWindow::
render(Image&  dst) noexcept
{
  Window::render(dst);

    if(Window::get_state() == WindowState::full_opened)
    {
      Point  const base_offset(rectangle.x+8,rectangle.y+8);

      int  w = menu.get_item_width();
      int  h = menu.get_item_height();

      menu.render(dst,base_offset,(column_number*y_base),column_number);


      Rectangle  rect(base_offset.x+(w*offset.x),
                      base_offset.y+(h*offset.y),w,h);

      dst.draw_rectangle(rect,Pixel(yellow,30000));
    }
}




}




