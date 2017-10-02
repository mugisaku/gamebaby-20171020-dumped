#include"gmbb_ColumnStyleMenuWindow.hpp"
#include"gmbb_environment.hpp"




namespace gmbb{


ColumnStyleMenuWindow::
ColumnStyleMenuWindow(Menu const&  menu_, int  page_n) noexcept:
menu(menu_),
page_number(page_n)
{
  Window::resize(menu.get_item_width()  +16,
                 menu.get_image_height()+16);
}




int
ColumnStyleMenuWindow::
get_item_index() const noexcept
{
  return (menu.get_row_number()*page_index)+row_index;
}


void
ColumnStyleMenuWindow::
reset_cursor() noexcept
{
  page_index = 0;
   row_index = 0;
}




void
ColumnStyleMenuWindow::
move_cursor_to_left()  noexcept
{
    if(page_index)
    {
      page_index -= 1;

      notify_needing_to_redraw();
    }
}


void
ColumnStyleMenuWindow::
move_cursor_to_right() noexcept
{
    if(page_index < (page_number-1))
    {
      page_index += 1;

      notify_needing_to_redraw();
    }
}


void
ColumnStyleMenuWindow::
move_cursor_to_up()    noexcept
{
    if(row_index)
    {
      row_index -= 1;

      notify_needing_to_redraw();
    }
}


void
ColumnStyleMenuWindow::
move_cursor_to_down()  noexcept
{
    if(row_index < (menu.get_row_number()-1))
    {
      row_index += 1;

      notify_needing_to_redraw();
    }
}




void
ColumnStyleMenuWindow::
change_row_number(int  n) noexcept
{
  menu.set_row_number(n);

  Window::resize(menu.get_item_width()  +16,
                 menu.get_image_height()+16);
}


void
ColumnStyleMenuWindow::
render(Image&  dst, Point  dst_point) const noexcept
{
  Window::render(dst,dst_point);

    if(Window::get_state() == WindowState::full_opened)
    {
      Point  const base_offset(dst_point+8);

      int  h = menu.get_item_height();

      menu.render(dst,base_offset,(menu.get_row_number()*page_index));


      Rectangle  rect(base_offset.x,
                      base_offset.y+(h*row_index),menu.get_item_width(),h);

      dst.draw_rectangle(rect,Pixel(yellow,30000));
    }
}




}




