#ifndef game_GameItem_HPP
#define game_GameItem_HPP


#include<cstdint>
#include<cstddef>


namespace game{


enum class
Condition
{
  null,
  sleep,
  poison,
  confuse,
  blind,
  illusion,
  seal,

};


enum class
GameItemKind
{
  null,

  sword,
  shield,
  belt,
  wand,
  card,

  empty,

};


struct
Sword
{
  uint8_t  strength;

  constexpr Sword(int  str): strength(str){}

};


struct
Shield
{
  uint8_t  strength;
};


struct
Belt
{
  uint8_t  effect;

};


struct
Wand
{
  uint8_t  effect;

};


struct
Card
{
  uint8_t  effect;

};


union
GameItemData
{
  Sword        sword;
  Shield      shield;
  Belt          belt;
  Wand          wand;
  Card          card;

   GameItemData() noexcept{}
  ~GameItemData()         {}

};


struct
Price
{
  int  value;

  constexpr Price(int  v=0) noexcept: value(v){}

};


class
GameItem
{
  char16_t const*  name=u"";

  Price  price;

  char16_t const*  description=u"";

  GameItemKind  kind=GameItemKind::empty;
  GameItemData  data;

public:
  GameItem() noexcept{}
  GameItem(char16_t const*  name_, Price  pri, char16_t const*  desc, Sword const&     swd) noexcept;
  GameItem(char16_t const*  name_, Price  pri, char16_t const*  desc, Shield const&    shl) noexcept;
  GameItem(char16_t const*  name_, Price  pri, char16_t const*  desc, Belt const&  blt) noexcept;
  GameItem(char16_t const*  name_, Price  pri, char16_t const*  desc, Wand const&  wnd) noexcept;
  GameItem(char16_t const*  name_, Price  pri, char16_t const*  desc, Card const&  crd) noexcept;

  GameItemData const*  operator->() const noexcept{return &data;}

  char16_t const*  get_name() const noexcept{return name;}
  char16_t const*  get_description() const noexcept{return description;}

  GameItemKind  get_kind() const noexcept{return kind;}

  Price  get_price() const noexcept{return price;}

  static GameItem const  empty;

};


extern GameItem const  game_item_table[];

extern size_t const  game_item_total;


}




#endif




