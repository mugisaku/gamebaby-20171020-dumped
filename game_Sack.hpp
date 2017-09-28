#ifndef game_Sack_HPP
#define game_Sack_HPP


#include"game_SackItem.hpp"
#include<algorithm>


namespace game{


constexpr int  sack_capacity = 16;


class
Sack
{
  SackItem     value_table[sack_capacity];
  SackItem*  pointer_table[sack_capacity];

  int  number_of_items=0;

public:
  Sack() noexcept;

  SackItem&  get_item(int  i) noexcept{return *pointer_table[i];}

  void       sort() noexcept;
  void  randomize() noexcept;

};


}




#endif




