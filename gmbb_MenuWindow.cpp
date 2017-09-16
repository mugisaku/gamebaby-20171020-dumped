#include"gmbb_MenuWindow.hpp"
#include"gmbb_environment.hpp"




namespace gmbb{


MenuWindow::
MenuWindow(Menu&  menu_, int  col_n, int  row_n, MenuItemRenderer  rend) noexcept:
Window(menu_.get_item_width()*col_n+16,menu_.get_item_height()*row_n+16),
menu(&menu_),
visible_column_number(col_n),
visible_row_number(row_n),
base_max(menu_.get_column_number()-col_n+1,menu_.get_row_number()-row_n+1),
id_max(menu_.get_item_width()*menu_.get_item_height()),
renderer(rend)
{
}




void
MenuWindow::
controll(Controller const&  ctrl) noexcept
{
  Window::controll(ctrl);

    if(Window::get_state() != WindowState::full_opened)
    {
      return;
    }


    if(ctrl.test(up_button_pressed))
    {
           if(offset.y){offset.y -= 1;}
      else if(base.y  ){base.y   -= 1;}

      notify_flag(needing_to_redraw);
    }

  else
    if(ctrl.test(down_button_pressed))
    {
           if(offset.y < (visible_row_number-1)){offset.y += 1;}
      else if(base.y   < (base_max.y        -1)){base.y   += 1;}

      notify_flag(needing_to_redraw);
    }

  else
    if(ctrl.test(left_button_pressed))
    {
           if(offset.x){offset.x -= 1;}
      else if(base.x  ){base.x   -= 1;}

      notify_flag(needing_to_redraw);
    }

  else
    if(ctrl.test(right_button_pressed))
    {
           if(offset.x < (visible_column_number-1)){offset.x += 1;}
      else if(base.x   < (base_max.x           -1)){base.x   += 1;}

      notify_flag(needing_to_redraw);
    }
}


void
MenuWindow::
render(Image&  dst) noexcept
{
  Window::render(dst);

    if(Window::get_state() == WindowState::full_opened)
    {
      Point  const base_offset(rectangle.x+8,rectangle.y+8);

      int  w = menu->get_item_width();
      int  h = menu->get_item_height();

        for(int  y = 0;  y < visible_row_number;     ++y){
        for(int  x = 0;  x < visible_column_number;  ++x){
          auto  id = menu->get_item_id(base.x+x,
                                       base.y+y);

            if(id.code < id_max)
            {
              Point  pt(base_offset.x+(w*x),
                        base_offset.y+(h*y));

              renderer(dst,pt,id);
            }
        }}


      Rectangle  rect(base_offset.x+(w*offset.x),
                      base_offset.x+(h*offset.y),w,h);

      dst.draw_rectangle(rect,yellow);
    }
}




}




