#include"gmbb_MenuWindow.hpp"
#include"gmbb_environment.hpp"




namespace gmbb{




MenuWindow::
MenuWindow(Menu&  menu_, int  col_n, int  row_n, MenuItemRenderer  rend) noexcept:
Window(menu_.get_item_width()*col_n+16,menu_.get_item_height()*row_n+16),
menu(&menu_),
visible_column_number(col_n),
visible_row_number(row_n),
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


}


void
MenuWindow::
render(Image&  dst) noexcept
{
  Window::render(dst);

    if(Window::get_state() == WindowState::full_opened)
    {
        for(int  y = 0;  y < visible_row_number;     ++y){
        for(int  x = 0;  x < visible_column_number;  ++x){
          auto&  i = menu->get_item(offset_point.x+x,
                                    offset_point.y+y);

          Point  pt(rectangle.x+8+(menu->get_item_width() *x),
                    rectangle.y+8+(menu->get_item_height()*y));

          renderer(dst,pt,i);
        }}
    }
}




}




