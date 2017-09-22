#include"game_Sack.hpp"
#include"gmbb_RandomNumber.hpp"




namespace game{




void
Sack::
randomize() noexcept
{
  gmbb::RandomNumber  r;

    for(auto&  i: item_table)
    {
      i.pointer = &game_item_table[r.generate(game_item_total-1)];
    }
}


}




