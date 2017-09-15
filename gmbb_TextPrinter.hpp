#ifndef GMBB_TextPrinter_HPP_INCLUDED
#define GMBB_TextPrinter_HPP_INCLUDED


#include<cstdint>
#include<cstdio>
#include<string>
#include<queue>
#include"gmbb_Figures.hpp"
#include"gmbb_Controller.hpp"
#include"gmbb_Image.hpp"
#include"gmbb_Text.hpp"




namespace gmbb{


class
TextPrinter
{
  Rectangle  rectangle;

  Text  text;

  GlyphSet const*  glyphset;

  int  fast_flag;

  int  scroll_count;
  int  scroll_key;
  int  finished_flag;

  char16_t  character_buffer[1024];

  char16_t const*  character_iterator;
  char16_t*        character_end;

  uint32_t  last_update_time;

  Pixel  pixels[2];

public:
  TextPrinter(GlyphSet&  glset, Point  point, int  column_number, int  row_number) noexcept;

  void  clear() noexcept;

  bool  is_finished() const noexcept;

  void  push(char16_t const*  src);
  void  push(std::initializer_list<char16_t const*>  ls);

  void  controll(Controller const&  ctrl) noexcept;

  void  render(Image&  dst) noexcept;

};


}




#endif




