#include"gmbb_MessageWindow.hpp"
#include"gmbb_environment.hpp"
#include<cctype>




namespace gmbb{


MessageWindow::
MessageWindow(GlyphSet&  glset, int  column_number, int  row_number) noexcept:
Window(glset.get_width( )*column_number+16,glset.get_height()*row_number+16),
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
  Window::set_state(WindowState::open_to_down);

  pixels[0].index = predefined_color_index::null;
  pixels[1].index = predefined_color_index::white;
}




namespace{
char16_t*
copy(const char16_t*  src, char16_t*  dst, const char16_t*  const dst_end) noexcept
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
sscan_id(const char16_t*  s, char16_t*  buf, size_t  n) noexcept
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
MessageWindow::
clear() noexcept
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
MessageWindow::
is_finished() const noexcept
{
  return finished_flag;
}


void
MessageWindow::
push(char16_t const*  src)
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
MessageWindow::
push(std::initializer_list<char16_t const*>  ls)
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
MessageWindow::
controll(Controller const&  ctrl) noexcept
{
  Window::controll(ctrl);

    if(Window::get_state() != WindowState::full_opened)
    {
      return;
    }


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
MessageWindow::
render(Image&  dst) noexcept
{
  Window::render(dst);

    if(Window::get_state() == WindowState::full_opened)
    {
      text.render(dst,Point(rectangle.x+8,rectangle.y+8),*glyphset,pixels);
    }
}




}



