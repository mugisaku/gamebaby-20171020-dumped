#ifndef GMBB_Menu_HPP_INCLUDED
#define GMBB_Menu_HPP_INCLUDED


#include<cstdint>
#include<algorithm>




namespace gmbb{


struct
ItemID
{
  uint16_t  code;

  constexpr ItemID(uint16_t  v=0) noexcept: code(v){}

};


class
Menu
{
  int  item_width;
  int  item_height;

  int  column_number;
  int     row_number;

public:
  Menu(int  item_w, int  item_h, int  col_n, int  row_n) noexcept;


  int  get_item_width() const noexcept{return item_width;}
  int  get_item_height() const noexcept{return item_height;}

  int  get_column_number() const noexcept{return column_number;}
  int  get_row_number() const noexcept{return row_number;}

  ItemID  get_item_id(int  x, int  y) const noexcept{return ItemID(column_number*y+x);}

};


}




#endif




