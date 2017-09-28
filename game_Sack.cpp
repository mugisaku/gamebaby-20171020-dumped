#include"game_Sack.hpp"
#include"gmbb_RandomNumber.hpp"




namespace game{




Sack::
Sack() noexcept
{
    for(int  i = 0;  i < sack_capacity;  ++i)
    {
      pointer_table[i] = &value_table[i];
    }
}




namespace{
bool
compare(SackItem const*  a, SackItem const*  b)
{
  return *a < *b;
}
}


void
Sack::
sort() noexcept
{
  std::stable_sort(std::begin(pointer_table),std::end(pointer_table),compare);
}


void
Sack::
randomize() noexcept
{
  gmbb::RandomNumber  r;

    for(auto&  i: value_table)
    {
      i = SackItem(r.generate(8000)&1? &game_item_table[r.generate(game_item_total-1)]:nullptr);
    }


  sort();
}


}




