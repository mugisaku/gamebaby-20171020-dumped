#ifndef game_Sack_HPP
#define game_Sack_HPP


#include"game_SackItem.hpp"
#include<algorithm>


namespace game{


constexpr int  sack_capacity = 16;


class
Sack
{
  SackItem  item_table[sack_capacity];

  int  number_of_items=0;

public:
  SackItem&  get_item(int  i) noexcept{return item_table[i];}

  void  sort() noexcept{std::stable_sort(std::begin(item_table),std::end(item_table));}

  void  randomize() noexcept;

};


}




#endif




