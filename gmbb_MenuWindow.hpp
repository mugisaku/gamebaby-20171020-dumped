#ifndef GMBB_MenuWindow_HPP_INCLUDED
#define GMBB_MenuWindow_HPP_INCLUDED


#include"gmbb_Figures.hpp"
#include"gmbb_Window.hpp"
#include"gmbb_Menu.hpp"




namespace gmbb{




using MenuItemRenderer = void  (*)(Image&  dst, Point  point, MenuItem const&  item);


class
MenuWindow: public Window
{
  Menu*  menu=nullptr;

  int  visible_column_number;
  int  visible_row_number;

  Point  offset_point;
  Point  cursor_point;

  MenuItemRenderer  renderer;

public:
  MenuWindow(Menu&  menu_, int  col_n, int  row_n, MenuItemRenderer  rend) noexcept;

  Point  get_offset_point() const noexcept{return offset_point;}
  Point  get_cursor_point() const noexcept{return cursor_point;}

  void  controll(Controller const&  ctrl) noexcept override;

  void  render(Image&  dst) noexcept override;

};


}




#endif




