#include"game_GameItem.hpp"


namespace game{




GameItem::
GameItem(char16_t const*  name_, Price  pri, char16_t const*  desc, Sword const&  swd) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::sword)
{data.sword = swd;}


GameItem::
GameItem(char16_t const*  name_, Price  pri, char16_t const*  desc, Shield const&  shl) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::shield)
{data.shield = shl;}


GameItem::
GameItem(char16_t const*  name_, Price  pri, char16_t const*  desc, Belt const&  blt) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::belt)
{data.belt = blt;}


GameItem::
GameItem(char16_t const*  name_, Price  pri, char16_t const*  desc, Wand const&  wnd) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::wand)
{data.wand = wnd;}


GameItem::
GameItem(char16_t const*  name_, Price  pri, char16_t const*  desc, Card const&  crd) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::card)
{data.card = crd;}




char16_t const*
GameItem::
get_first_operation_name() const noexcept
{
    if((kind == GameItemKind::sword ) ||
       (kind == GameItemKind::shield) ||
       (kind == GameItemKind::belt  ))
    {
      return u"そうび";
    }

  else
    if(kind == GameItemKind::wand)
    {
      return u"ふる";
    }

  else
    if(kind == GameItemKind::card)
    {
      return u"となえる";
    }


  return nullptr;
}


GameItem const
GameItem::
empty;


GameItem const
game_item_table[] =
{
  GameItem(u"きのぼう"        ,Price(0),u"",Sword(0)),
  GameItem(u"きんぞくのぼう"  ,Price(0),u"",Sword(0)),
  GameItem(u"せいどうのつるぎ",Price(0),u"",Sword(0)),
  GameItem(u"てつのつるぎ"    ,Price(0),u"",Sword(0)),
  GameItem(u"はがねのつるぎ"  ,Price(0),u"",Sword(0)),
  GameItem(u"ぎんのつるぎ"    ,Price(0),u"",Sword(0)),
  GameItem(u"おうごんのつるぎ",Price(0),u"",Sword(0)),
};


size_t const
game_item_total = sizeof(game_item_table)/sizeof(GameItem);


}




