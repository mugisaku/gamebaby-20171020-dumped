#include"gmbb_MenuWindow.hpp"
#include"gmbb_environment.hpp"




namespace gmbb{


MenuWindow::
MenuWindow(Menu const&  menu_, MenuItemRenderer  rend, int  col_n, int  row_n) noexcept:
menu(menu_),
visible_column_number(col_n? col_n:menu.get_column_number()),
visible_row_number(   row_n? row_n:menu.get_row_number()   ),
id_max(menu_.get_item_width()*menu_.get_item_height()),
renderer(rend)
{
  Window::resize(menu.get_item_width() *visible_column_number+16,
                 menu.get_item_height()*visible_row_number   +16);

  base_max = Point(menu.get_column_number()-visible_column_number+1,
                   menu.get_row_number()   -visible_row_number   +1);
}




void
MenuWindow::
reset_cursor() noexcept
{
  base   = Point();
  offset = Point();
}




void
MenuWindow::
move_cursor_to_left()  noexcept
{
       if(offset.x){offset.x -= 1;}
  else if(base.x  ){base.x   -= 1;}

  notify_flag(needing_to_redraw);
}


void
MenuWindow::
move_cursor_to_right() noexcept
{
       if(offset.x < (visible_column_number-1)){offset.x += 1;}
  else if(base.x   < (base_max.x           -1)){base.x   += 1;}

  notify_flag(needing_to_redraw);
}


void
MenuWindow::
move_cursor_to_up()    noexcept
{
       if(offset.y){offset.y -= 1;}
  else if(base.y  ){base.y   -= 1;}

  notify_flag(needing_to_redraw);
}


void
MenuWindow::
move_cursor_to_down()  noexcept
{
       if(offset.y < (visible_row_number-1)){offset.y += 1;}
  else if(base.y   < (base_max.y        -1)){base.y   += 1;}

  notify_flag(needing_to_redraw);
}




void
MenuWindow::
render(Image&  dst) noexcept
{
  Window::render(dst);

    if(Window::get_state() == WindowState::full_opened)
    {
      Point  const base_offset(rectangle.x+8,rectangle.y+8);

      int  w = menu.get_item_width();
      int  h = menu.get_item_height();

        for(int  y = 0;  y < visible_row_number;     ++y){
        for(int  x = 0;  x < visible_column_number;  ++x){
          auto  i = menu.get_item_index(Point(base.x+x,
                                              base.y+y));

            if(i < id_max)
            {
              Point  pt(base_offset.x+(w*x),
                        base_offset.y+(h*y));

              renderer(dst,pt,i);
            }
        }}


      Rectangle  rect(base_offset.x+(w*offset.x),
                      base_offset.x+(h*offset.y),w,h);

      dst.draw_rectangle(rect,yellow);
    }
}




}




