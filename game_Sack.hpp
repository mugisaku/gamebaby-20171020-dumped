#ifndef game_Sack_HPP
#define game_Sack_HPP


#include"game_SackItem.hpp"
#include<algorithm>


namespace gmbb{


constexpr int  sack_capacity = 16;


class
Sack
{
  SackItem     value_table[sack_capacity];
  SackItem*  pointer_table[sack_capacity];

public:
  Sack() noexcept;

  SackItem&  get_item(int  i) noexcept{return *pointer_table[i];}

  void  clear() noexcept;

  covered_ptr<SackItem>  find_empty() noexcept;

  bool  try_to_push_item(SackItem const&  item) noexcept;

  void       sort() noexcept;
  void  randomize() noexcept;

};


}




#endif




