#ifndef GMBB_Menu_HPP_INCLUDED
#define GMBB_Menu_HPP_INCLUDED


#include<cstdint>
#include<algorithm>
#include"gmbb_Figures.hpp"




namespace gmbb{


class
Menu
{
  int  item_width;
  int  item_height;

  int  column_number;
  int     row_number;

public:
  Menu(int  item_w, int  item_h, int  col_n, int  row_n) noexcept;


  int  get_item_width()  const noexcept{return item_width;}
  int  get_item_height() const noexcept{return item_height;}

  int  get_column_number() const noexcept{return column_number;}
  int  get_row_number()    const noexcept{return    row_number;}

  int  get_item_index(Point  point) const noexcept{return (column_number*point.y+point.x);}

};


}




#endif




