#ifndef game_Sack_HPP
#define game_Sack_HPP


#include"game_GameItem.hpp"
#include"covered_ptr"


namespace game{


struct
SackItem
{
  GameItem const*  pointer=&GameItem::empty;

  uint8_t  number;

  operator bool() const noexcept{return pointer;}

  GameItem const*  operator->() const noexcept{return  pointer;}
  GameItem const&  operator *() const noexcept{return *pointer;}

};


constexpr int  sack_capacity = 16;


class
Sack
{
  SackItem  item_table[sack_capacity];

public:
  SackItem&  get_item(int  i) noexcept{return item_table[i];}

  void  randomize() noexcept;

};


}




#endif




