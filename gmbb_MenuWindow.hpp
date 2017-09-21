#ifndef GMBB_MenuWindow_HPP_INCLUDED
#define GMBB_MenuWindow_HPP_INCLUDED


#include"gmbb_Figures.hpp"
#include"gmbb_Window.hpp"
#include"gmbb_Menu.hpp"




namespace gmbb{




using MenuItemRenderer = void  (*)(Image&  dst, Point  point, int  index);


class
MenuWindow: public Window
{
  Menu  menu;

  int  visible_column_number;
  int  visible_row_number;

  Point  base_max;
  Point  base;
  Point  offset;

  int  id_max;

  bool  base_locking=false;

  MenuItemRenderer  renderer;

public:
  MenuWindow(Menu const&  menu_, MenuItemRenderer  rend, int  col_n=0, int  row_n=0) noexcept;

  Point  get_base_point() const noexcept{return base;}
  Point  get_cursor_point() const noexcept{return base+offset;}

  int  get_item_index() const noexcept{return menu.get_item_index(base+offset);}

  void  move_cursor_to_left()  noexcept;
  void  move_cursor_to_right() noexcept;
  void  move_cursor_to_up()    noexcept;
  void  move_cursor_to_down()  noexcept;

  void  change_visible_row_number(int  v) noexcept;

  void    lock_base() noexcept{base_locking =  true;}
  void  unlock_base() noexcept{base_locking = false;}

  void  reset_cursor() noexcept;

  void  render(Image&  dst) noexcept override;

};


}




#endif




