#include"game_Piece.hpp"
#include"game_Board.hpp"
#include"gmbb_unicode.hpp"
#include<new>


namespace game{


namespace{
gmbb::Rectangle
get_image_rectangle(Piece const&  p) noexcept
{
  int  w = square_size;

  constexpr int  h = 48;

  int  x = 0;
  int  y = 0;

    switch(p.get_frame_index())
    {
  case(0): x = 0  ;break;
  case(1): x = w  ;break;
  case(2): x = 0  ;break;
  case(3): x = w*2;break;
    }


    switch(p.get_face_direction())
    {
  case(Direction::front):
      break;
  case(Direction::front_left):
      y = h*3;
      break;
  case(Direction::left):
      y = h*1;
      break;
  case(Direction::back_left):
      y = h*4;
      break;
  case(Direction::back):
      y = h*2;
      break;
  case(Direction::back_right):
      y = h*4;
      w = -w;
      break;
  case(Direction::right):
      y = h*1;
      w = -w;
      break;
  case(Direction::front_right):
      y = h*3;
      w = -w;
      break;
    }


  return gmbb::Rectangle(x,y,w,h);
}


void
revise_point(gmbb::Point&  point, gmbb::Rectangle const&   rect) noexcept
{
    if(point.x < -rect.w)
    {
        while(point.x < -rect.w)
        {
          point.x += board_image_width;
        }
    }

  else
    if(point.x >= board_image_width+rect.w)
    {
        while(point.x >= board_image_width+rect.w)
        {
          point.x -= board_image_width;
        }
    }


    if(point.y < -rect.h)
    {
        while(point.y < -rect.h)
        {
          point.y += board_image_height;
        }
    }

  else
    if(point.y >= board_image_height+rect.h)
    {
        while(point.y >= board_image_height+rect.h)
        {
          point.y -= board_image_height;
        }
    }
}


}


void
Piece::
render(gmbb::Image&  dst, gmbb::Point  dst_point) const noexcept
{
  auto  rect = get_image_rectangle(*this);

  dst_point.y -= square_size;

  revise_point(dst_point,rect);

  int  z = dst_point.y;

  dst.transfer(*get_source_image(),rect,dst_point,board_image_height+z);
}




}




