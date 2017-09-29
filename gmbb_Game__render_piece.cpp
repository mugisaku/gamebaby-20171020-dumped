#include"gmbb_Game_private.hpp"


namespace gmbb{


using  game::Piece;
using game::Square;
using game::Direction;


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
revise_point(Point&  point, Rectangle const&   rect) noexcept
{
    if(point.x < -rect.w)
    {
        while(point.x < -rect.w)
        {
          point.x += board_image_w;
        }
    }

  else
    if(point.x >= board_image_w+rect.w)
    {
        while(point.x >= board_image_w+rect.w)
        {
          point.x -= board_image_w;
        }
    }


    if(point.y < -rect.h)
    {
        while(point.y < -rect.h)
        {
          point.y += board_image_h;
        }
    }

  else
    if(point.y >= board_image_h+rect.h)
    {
        while(point.y >= board_image_h+rect.h)
        {
          point.y -= board_image_h;
        }
    }
}


}


void
update_piece(game::Piece&  p) noexcept
{
  p.increase_frame_index_when_over(8);

    if(p.get_frame_index() >= 4)
    {
      p.reset_frame();
    }
}


void
render_piece(game::Piece const&  p, Image&  dst, Point  dst_point) noexcept
{
  auto  rect = get_image_rectangle(p);

  dst_point.y -= square_size;

  revise_point(dst_point,rect);

  int  z = dst_point.y;


  dst.transfer(character_image,rect,dst_point,board_image_h+z);
}


}




