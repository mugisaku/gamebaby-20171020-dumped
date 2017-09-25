#include"game_Piece.hpp"
#include"game_Board.hpp"
#include<new>


namespace game{




void
Piece::
reset(Hero&  hero) noexcept
{
  data.hero  = &hero;

  name = hero.get_name();

  hp     = 20;
  hp_max = 20;
}


void
Piece::
reset(Enemy&  enem) noexcept
{
  data.enemy = &enem;
}


void
Piece::
change_equipment(covered_ptr<SackItem>  p) noexcept
{
    if(p)
    {
      auto&  item = *p;

        switch(item->get_kind())
        {
      case(GameItemKind::sword):
          sword_item = (sword_item == p)? nullptr:p;
          break;
      case(GameItemKind::shield):
          shield_item = (shield_item == p)? nullptr:p;
          break;
      case(GameItemKind::belt):
          belt_item = (belt_item == p)? nullptr:p;
          break;
      default:;
        }
    }
}


gmbb::Rectangle
Piece::
get_image_rectangle() const noexcept
{
  int  w = 24;

  constexpr int  h = 48;

  int  x = 0;
  int  y = 0;

    switch(frame_count)
    {
  case(0): x = 0  ;break;
  case(1): x = w  ;break;
  case(2): x = 0  ;break;
  case(3): x = w*2;break;
    }

    switch(direction)
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
Piece::
step() noexcept
{
    if(wait_count)
    {
      --wait_count;

      return;
    }


  wait_count = wait_value;

    if(++frame_count >= 4)
    {
      frame_count = 0;
    }
}


}




