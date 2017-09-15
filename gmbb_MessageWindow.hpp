#ifndef GMBB_MessageWindow_HPP_INCLUDED
#define GMBB_MessageWindow_HPP_INCLUDED


#include"gmbb_Figures.hpp"
#include"gmbb_Window.hpp"
#include"gmbb_Text.hpp"




namespace gmbb{


class
MessageWindow: public Window
{
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
  MessageWindow(GlyphSet&  glset, int  column_number, int  row_number) noexcept;

  void  clear() noexcept;

  bool  is_finished() const noexcept;

  void  push(char16_t const*  src);
  void  push(std::initializer_list<char16_t const*>  ls);

  void  controll(Controller const&  ctrl) noexcept override;

  void  render(Image&  dst) noexcept override;

};


}




#endif




