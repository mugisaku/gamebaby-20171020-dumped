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


GameItem::
GameItem(char16_t const*  name_, Price  pri, char16_t const*  desc, Water const&  wat) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::water)
{data.water = wat;}




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

  else
    if(kind == GameItemKind::water)
    {
      return u"あびる";
    }


  return nullptr;
}


GameItem const
game_item_table[] =
{
  GameItem(u"きのぼう"        ,Price(0),u"",Sword(0)),
  GameItem(u"きんぞくのぼう"  ,Price(0),u"",Sword(0)),
  GameItem(u"せいどうのつるぎ",Price(0),u"",Sword(0)),
  GameItem(u"てつのつるぎ"    ,Price(0),u"",Sword(0)),
  GameItem(u"はがねのつるぎ"  ,Price(0),u"",Sword(0)),
  GameItem(u"ぎんのつるぎ"    ,Price(0),u"",Sword(0)),
  GameItem(u"みょうおうのつるぎ",Price(0),u"",Sword(0)),
  GameItem(u"きのたて",Price(0),u"",Shield(0)),
  GameItem(u"かわのたて",Price(0),u"",Shield(0)),
  GameItem(u"てつのたて",Price(0),u"",Shield(0)),
  GameItem(u"はがねのたて",Price(0),u"",Shield(0)),
  GameItem(u"やすいおび",Price(0),u"",Belt()),
  GameItem(u"ふつうのおび",Price(0),u"",Belt()),
  GameItem(u"こうきゅうおび",Price(0),u"",Belt()),
  GameItem(u"まよけのおび",Price(0),u"",Belt()),
  GameItem(u"ちからのおび",Price(0),u"",Belt()),
  GameItem(u"くろおび",Price(0),u"",Belt()),
  GameItem(u"こううんのおび",Price(0),u"",Belt()),
  GameItem(u"ふこうのおび",Price(0),u"",Belt()),
  GameItem(u"ねむりのつえ",Price(0),u"",Wand()),
  GameItem(u"どくのつえ",Price(0),u"",Wand()),
  GameItem(u"ふういんのつえ",Price(0),u"",Wand()),
  GameItem(u"てんいのつえ",Price(0),u"",Wand()),
  GameItem(u"いれかえのつえ",Price(0),u"",Wand()),
  GameItem(u"ほのおのつえ",Price(0),u"",Wand()),
  GameItem(u"つちのつえ",Price(0),u"",Wand()),
  GameItem(u"こんらんのつえ",Price(0),u"",Wand()),
  GameItem(u"くらやみのつえ",Price(0),u"",Wand()),
  GameItem(u"へんげのつえ",Price(0),u"",Wand()),
  GameItem(u"げんえいのつえ",Price(0),u"",Wand()),
  GameItem(u"ちからのふだ",Price(0),u"",Card()),
  GameItem(u"まもりのふだ",Price(0),u"",Card()),
  GameItem(u"こうてつのふだ",Price(0),u"",Card()),
  GameItem(u"だっしゅつのふだ",Price(0),u"",Card()),
  GameItem(u"いやしのみず",Price(0),u"",Water()),
  GameItem(u"いのちのみず",Price(0),u"",Water()),
  GameItem(u"どくのみず",Price(0),u"",Water()),
  GameItem(u"げどくのみず",Price(0),u"",Water()),
  GameItem(u"きよめのみず",Price(0),u"",Water()),
  GameItem(u"ただのみず",Price(0),u"",Water()),
  GameItem(u"くさいのみず",Price(0),u"",Water()),
  GameItem(u"きせきのみず",Price(0),u"",Water()),
};


size_t const
game_item_total = sizeof(game_item_table)/sizeof(GameItem);


}




