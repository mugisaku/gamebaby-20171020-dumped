#ifndef game_SackItem_HPP
#define game_SackItem_HPP


#include"game_GameItem.hpp"
#include"covered_ptr"


namespace gmbb{


enum class
SackItemFlag
{
  be_equipped  = 0x1,
  cursed       = 0x2,

};


class
SackItem
{
  GameItem const*  pointer=nullptr;

  uint8_t  flags=0;

  int8_t  number;

public:
  constexpr SackItem(GameItem const*  p=nullptr, uint8_t  flags_=0, int8_t  n=0) noexcept:
  pointer(p), flags(flags_), number(n){}


  constexpr operator bool() const noexcept{return pointer;}

  bool  operator<(SackItem const&  rhs) const noexcept;

  constexpr GameItem const*  operator->() const noexcept{return  pointer;}
  constexpr GameItem const&  operator *() const noexcept{return *pointer;}

  constexpr int8_t  get_number() const noexcept{return number;}

  void    set_flag(SackItemFlag  flag) noexcept{flags |=  static_cast<int>(flag);}
  void  unset_flag(SackItemFlag  flag) noexcept{flags &= ~static_cast<int>(flag);}
  constexpr bool   test_flag(SackItemFlag  flag) const noexcept{return flags&static_cast<int>(flag);}

  constexpr bool  is_equipped() const noexcept{return test_flag(SackItemFlag::be_equipped);}
  constexpr bool    is_cursed() const noexcept{return test_flag(SackItemFlag::cursed);}

};


}




#endif




