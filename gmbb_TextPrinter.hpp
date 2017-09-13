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

  const char16_t*  character_iterator;
        char16_t*  character_end;

  uint32_t  last_update_time;

public:
  TextPrinter(int  column_number, int  row_number);

  void  clear();

  bool  is_finished() const;

  void  push(const char16_t*   src);
  void  push(std::initializer_list<const char16_t*>  ls);

  void  controll(const Controller&  ctrl);

  void  update();

  void  render(Image&  dst);

};


}




#endif




