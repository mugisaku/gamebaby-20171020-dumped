#include"gmbb_TextPrinter.hpp"
#include"gmbb_environment.hpp"
#include<cctype>




namespace gmbb{


TextPrinter::
TextPrinter(GlyphSet&  glset, Point  point, int  column_number, int  row_number):
glyphset(&glset),
text(column_number,row_number),
fast_flag(0),
scroll_count(0),
scroll_key(0),
finished_flag(1),
character_iterator(character_buffer),
character_end(character_buffer),
last_update_time(0)
{
  rectangle = Rectangle(point.x,point.y,glset.get_width( )*column_number,
                                        glset.get_height()*row_number);

  pixels[0].index = predefined_color_index::null;
  pixels[1].index = predefined_color_index::white;
}




namespace{
char16_t*
copy(const char16_t*  src, char16_t*  dst, const char16_t*  const dst_end)
{
    if(dst == dst_end)
    {
      return dst;
    }


    while(dst < dst_end)
    {
      auto  c = *src++;

        if(!c)
        {
          break;
        }


      *dst++ = c;
    }


  *dst = 0;

  return dst;
}


int
sscan_id(const char16_t*  s, char16_t*  buf, size_t  n)
{
  int  r = 0;

    if(!n)
    {
      return 0;
    }


    if(n == 1)
    {
      *buf = 0;

      return 0;
    }


  auto  c = *s++;

    if(isalpha(c) || (c == '_'))
    {
      *buf++ = c;

      --n;
      ++r;

        for(;;)
        {
            if(n == 1)
            {
              break;
            }


          c = *s++;

            if(isalnum(c) || (c == '_'))
            {
              *buf++ = c;

              --n;
              ++r;
            }

          else
            {
              break;
            }
        }
    }


  *buf = 0;

  return r;
}
}




void
TextPrinter::
clear()
{
  text.clear();

  scroll_count  = 0;
  scroll_key    = 0;
  fast_flag     = 0;
  finished_flag = 1;

  character_iterator = character_buffer;
  character_end      = character_buffer;
}


bool
TextPrinter::
is_finished() const
{
  return finished_flag;
}


void
TextPrinter::
push(const char16_t*  src)
{
    if(finished_flag)
    {
      clear();

      finished_flag = 0;
    }


    while(character_end < std::end(character_buffer))
    {
      auto  c = *src++;

        if(c == '$')
        {
          char16_t  tmpbuf[256];

          auto  n = sscan_id(src,tmpbuf,256);

            if(!n)
            {
              printf("環境変数をを指す識別子が不正です\n");

              throw;
            }


          src += n;

          character_end = copy(env::get_value(tmpbuf).data(),character_end,std::end(character_buffer));
        }

      else
        if(!c)
        {
          break;
        }

      else
        {
          *character_end++ = c;
        }
    }


  *character_end = 0;
}


void
TextPrinter::
push(std::initializer_list<const char16_t*>  ls)
{
    for(auto  s: ls)
    {
        if((character_end > std::begin(character_buffer)) &&
           (character_end < std::end(  character_buffer)))
        {
          *character_end++ = '\n';
        }


      push(s);
    }
}


void
TextPrinter::
controll(const Controller&  ctrl)
{
    if(ctrl.test(p_button_pressed))
    {
        if((character_iterator == character_end) && !scroll_count)
        {
          finished_flag = 1;

          return;
        }
    }


    if(ctrl.test(p_button_pressed))
    {
      fast_flag = 1;

        if((character_iterator != character_end))
        {
            if(scroll_key)
            {
              scroll_count = rectangle.h/2;

              scroll_key = 0;
            }
        }
    }

  else
    if(ctrl.test(p_button_released))
    {
      fast_flag = 0;
    }


    if(character_iterator == character_end)
    {
      return;
    }


  constexpr uint32_t  interval_time_base = 80;

  auto  now = ctrl.get_time();

  auto  interval_time = interval_time_base;

    if(fast_flag)
    {
      interval_time /= 3;
    }


    if(now > (last_update_time+interval_time))
    {
      last_update_time = now;

        if(!text.is_full())
        {
          text.push(*character_iterator++);
        }

      else
        if(scroll_count)
        {
          text.rotate();

          scroll_count -= 1;
        }

      else
        {
          scroll_key = 1;
        }
    }
}


void
TextPrinter::
render(Image&  dst)
{
  dst.fill();

  text.render(dst,rectangle,*glyphset,pixels);
}




}




