#ifndef GMBB_ScrollStyleMenuWindow_HPP_INCLUDED
#define GMBB_ScrollStyleMenuWindow_HPP_INCLUDED


#include"gmbb_Figures.hpp"
#include"gmbb_Window.hpp"
#include"gmbb_Menu.hpp"




namespace gmbb{




class
ScrollStyleMenuWindow: public Window
{
  Menu  menu;

  int  column_number;
  int     row_number;

  int  y_base=0;

  Point  offset;

public:
  ScrollStyleMenuWindow(Menu const&  menu_, int  col_n, int  row_n) noexcept;

  int  get_item_index() const noexcept{return (column_number*(y_base+offset.y))+offset.x;}

  void  move_cursor_to_left()  noexcept;
  void  move_cursor_to_right() noexcept;
  void  move_cursor_to_up()    noexcept;
  void  move_cursor_to_down()  noexcept;

  void  reset_cursor() noexcept;

  void  render(Image&  dst, Point  dst_point) const noexcept override;

};


}




#endif




