#include"gmbb_Image.hpp"
#include<cstring>



namespace gmbb{




void
Image::
draw_dot(Point  pt, Pixel  pix) noexcept
{
    if(pix.index)
    {
      auto&  dst = this->pixels[(this->width*pt.y)+pt.x];

        if(dst.z <= pix.z)
        {
          dst = pix;
        }
    }
}


void
Image::
draw_dot_safety(Point  pt, Pixel  pix) noexcept
{
    if((pt.x >=            0) &&
       (pt.x <   this->width) &&
       (pt.y >=            0) &&
       (pt.y <  this->height))
    {
      draw_dot(pt,pix);
    }
}


void
Image::
draw_vline(Point  pt, int  l, Pixel  pix) noexcept
{
    while(l--)
    {
      draw_dot(pt,pix);

      pt.y += 1;
    }
}


void
Image::
draw_hline(Point  pt, int  l, Pixel  pix) noexcept
{
    while(l--)
    {
      draw_dot(pt,pix);

      pt.x += 1;
    }
}


void
Image::
draw_rectangle(Rectangle const&  rect, Pixel  pix) noexcept
{
  draw_hline(Point(rect.x,rect.y         ),rect.w,pix);
  draw_hline(Point(rect.x,rect.y+rect.h-1),rect.w,pix);

  draw_vline(Point(rect.x         ,rect.y+1),rect.h-2,pix);
  draw_vline(Point(rect.x+rect.w-1,rect.y+1),rect.h-2,pix);
}


void
Image::
fill_rectangle(Rectangle  rect, Pixel  pix) noexcept
{
    while(rect.h--)
    {
      draw_hline(rect,rect.w,pix);

      ++rect.y;
    }
}


}





