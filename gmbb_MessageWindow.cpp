#include"gmbb_MessageWindow.hpp"
#include"gmbb_environment.hpp"
#include<cctype>




namespace gmbb{


MessageWindow::
MessageWindow(GlyphSet&  glset, int  column_number, int  row_number) noexcept:
Window(glset.get_width( )*column_number+16,glset.get_height()*row_number+16),
glyphset(&glset),
text(column_number,row_number),
input_pointer( buffer),
output_pointer(buffer)
{
  Window::set_state(WindowState::open_to_down);

  coloring[1] = white;
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

  reset();
}


void
MessageWindow::
reset() noexcept
{
   input_pointer = buffer;
  output_pointer = buffer;
}


void
MessageWindow::
push(char16_t const*  src)
{
    while((input_pointer < std::end(buffer)) && *src)
    {
      *input_pointer++ = *src++;
    }
}


void
MessageWindow::
push(std::initializer_list<char16_t const*>  ls)
{
    for(auto  s: ls)
    {
      push(s);

      push(u"\n");
    }
}


void
MessageWindow::
step()
{
    if(output_pointer != input_pointer)
    {
        if(!text.is_full())
        {
          text.push(*output_pointer++);

          notify_needing_to_redraw();
        }
    }
}


void
MessageWindow::
scroll()
{
  text.rotate();

  notify_needing_to_redraw();
}


void
MessageWindow::
render(Image&  dst, Point  dst_point) const noexcept
{
  Window::render(dst,dst_point);

    if(Window::get_state() == WindowState::full_opened)
    {
      text.render(dst,dst_point+8,*glyphset,coloring);
    }
}




}




