#include"game_Piece.hpp"
#include"game_Board.hpp"
#include"gmbb_unicode.hpp"
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
hold_item(covered_ptr<SackItem>  p) noexcept
{
    if(p)
    {
        if(unhold_item(p))
        {
          return;
        }


      auto&  item = *p;

        switch(item->get_kind())
        {
      case(GameItemKind::sword):
          unhold_sword();

                       p->set_flag(SackItemFlag::be_equipped);
          sword_item = p                                     ;
          break;
      case(GameItemKind::shield):
          unhold_shield();

                        p->set_flag(SackItemFlag::be_equipped);
          shield_item = p                                     ;
          break;
      case(GameItemKind::belt):
          unhold_belt();

                      p->set_flag(SackItemFlag::be_equipped);
          belt_item = p                                     ;
          break;
      default:;
        }


//printf("+%s を装備した\n",gmbb::to_string((*p)->get_name()).data());
    }
}


bool
Piece::
unhold_item(covered_ptr<SackItem>  p) noexcept
{
  bool  res = false;

       if( sword_item == p){ unhold_sword();  res = true;}
  else if(shield_item == p){unhold_shield();  res = true;}
  else if(  belt_item == p){  unhold_belt();  res = true;}


  return res;
}


namespace{
void
unhold(covered_ptr<SackItem>&  p) noexcept
{
    if(p)
    {
//printf("-%s を外した\n",gmbb::to_string((*p)->get_name()).data());
      p->unset_flag(SackItemFlag::be_equipped);

      p = nullptr;
    }
}
}


void  Piece::unhold_sword()  noexcept{unhold( sword_item);}
void  Piece::unhold_shield() noexcept{unhold(shield_item);}
void  Piece::unhold_belt()   noexcept{unhold(  belt_item);}


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




