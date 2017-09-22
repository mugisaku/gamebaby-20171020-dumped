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


}




