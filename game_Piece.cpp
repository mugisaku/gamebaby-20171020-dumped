#include"game_Piece.hpp"
#include"game_Square.hpp"




namespace gmbb{




void
Piece::
reset(Hero&  hero) noexcept
{
  name = hero.get_name();

  hp     = 20;
  hp_max = 20;
}


void
Piece::
reset(Enemy&  enem) noexcept
{
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
set_position_by_current_square() noexcept
{
  PieceBase::update();

  set_x_position(fixed_t(square_size*square->get_x()));
  set_y_position(fixed_t(square_size*square->get_y()));
}


}




