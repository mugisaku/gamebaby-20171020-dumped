#ifndef game_Sack_HPP
#define game_Sack_HPP


#include"game_GameItem.hpp"


namespace game{


struct
SackItem
{
  GameItem const*  pointer=&GameItem::empty;

  uint8_t  number;

  GameItem const*  operator->() const noexcept{return  pointer;}
  GameItem const&  operator *() const noexcept{return *pointer;}

};


constexpr int  sack_capacity = 16;


struct
Sack
{
  SackItem  item_table[sack_capacity];

};


}




#endif




