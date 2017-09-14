#ifndef GMBB_TEXT_HPP_INCLUDED
#define GMBB_TEXT_HPP_INCLUDED


#include<cstdint>
#include<cstdio>
#include<string>
#include<queue>
#include"gmbb_Figures.hpp"
#include"gmbb_Controller.hpp"
#include"gmbb_Image.hpp"




namespace gmbb{


class
Text
{
  struct Line;

  int  column_number;
  int     row_number;

  Line*    first;
  Line*  current;
  Line*     last;

  char16_t  last_char;

public:
  Text(int  col_n, int  row_n);

  void  clear();

  void  rotate();

  void  push(char16_t  c);

  bool  is_full() const;

  void  render(Image&  dst, Point  point, GlyphSet const&  glset, Pixel const*  pixels) const;

};


}




#endif




