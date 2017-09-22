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




}




