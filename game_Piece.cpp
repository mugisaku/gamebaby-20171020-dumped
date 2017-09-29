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




void
Piece::
reset_frame() noexcept
{
  frame_count = 0;
  frame_index = 0;
}


void
Piece::
increase_frame_index_when_over(int  limit) noexcept
{
    if(frame_count >= limit)
    {
      frame_count  = 0;
      frame_index += 1;
    }
}


void
Piece::
change_action_index(int  v) noexcept
{
  action_index = v;

  reset_frame();
}


void
Piece::
set_rendering_point_by_current_square(int  square_size) noexcept
{
  auto&  sq = *square;

  rendering_point = gmbb::Point(square_size*sq.get_x(),
                                square_size*sq.get_y());
}


void
Piece::
step() noexcept
{
  ++frame_count;

    if(update_callback)
    {
      update_callback(*this);
    }


    if(action_stack.size())
    {
      auto&  act = action_stack.back();

      act.callback(*this,--act.count);

        if(!act.count)
        {
          action_stack.pop_back();
        }
    }
}


}




