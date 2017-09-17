#ifndef GMBB_MenuWindow_HPP_INCLUDED
#define GMBB_MenuWindow_HPP_INCLUDED


#include"gmbb_Figures.hpp"
#include"gmbb_Window.hpp"
#include"gmbb_Menu.hpp"




namespace gmbb{




using MenuItemRenderer = void  (*)(Image&  dst, Point  point, ItemID  id);


enum class
MenuOperation
{
  none,
  show,
  choose_one,
  choose_two,

};


class
MenuWindow: public Window
{
  Menu  menu;

  MenuOperation  operation=MenuOperation::none;

  int  visible_column_number;
  int  visible_row_number;

  Point  base_max;
  Point  base;
  Point  offset;

  Point  first_choice;

  bool first_item_was_chosen=false;

  int  id_max;

  MenuItemRenderer  renderer;

public:
  MenuWindow(Menu const&  menu_, MenuItemRenderer  rend, int  col_n=0, int  row_n=0) noexcept;

  Point  get_base_point() const noexcept{return base;}
  Point  get_cursor_point() const noexcept{return base+offset;}

  void  move_cursor_to_left()  noexcept;
  void  move_cursor_to_right() noexcept;
  void  move_cursor_to_up()    noexcept;
  void  move_cursor_to_down()  noexcept;

  void  change_operation(MenuOperation  o) noexcept{operation = o;}

  void  reset_cursor() noexcept;

  void  render(Image&  dst) noexcept override;

};


}




#endif




