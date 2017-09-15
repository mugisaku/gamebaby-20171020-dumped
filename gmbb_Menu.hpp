#ifndef GMBB_Menu_HPP_INCLUDED
#define GMBB_Menu_HPP_INCLUDED


#include<cstdint>
#include<algorithm>




namespace gmbb{


struct
MenuItem
{
  uint16_t  id=0;

  constexpr MenuItem(uint16_t  id_=0xFFFF): id(id_){}

};


class
Menu
{
  MenuItem*  item_table;

  int  item_width;
  int  item_height;

  int  column_number;
  int     row_number;

public:
  Menu(int  item_w, int  item_h, int  col_n, int  row_n) noexcept;
  Menu(Menu const&  rhs) noexcept=delete;
  Menu(Menu&&       rhs) noexcept=delete;
 ~Menu(){delete[] item_table;}


  int  get_item_width() const noexcept{return item_width;}
  int  get_item_height() const noexcept{return item_height;}

  int  get_column_number() const noexcept{return column_number;}
  int  get_row_number() const noexcept{return row_number;}

  MenuItem&  get_item(int  x, int  y) noexcept{return item_table[(column_number*y)+x];}

  void  put_item(MenuItem  i, int  x, int  y) noexcept{item_table[(column_number*y)+x] = i;}

  void  fill() noexcept{std::fill(item_table,item_table+(column_number*row_number),MenuItem());}

};


}




#endif




