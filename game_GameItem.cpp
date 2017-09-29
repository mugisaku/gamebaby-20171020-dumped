#include"game_GameItem.hpp"


namespace game{




GameItem::
GameItem(char const*  name_, Price  pri, char16_t const*  desc, Sword const&  swd) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::sword)
{data.sword = swd;}


GameItem::
GameItem(char const*  name_, Price  pri, char16_t const*  desc, Shield const&  shl) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::shield)
{data.shield = shl;}


GameItem::
GameItem(char const*  name_, Price  pri, char16_t const*  desc, Belt const&  blt) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::belt)
{data.belt = blt;}


GameItem::
GameItem(char const*  name_, Price  pri, char16_t const*  desc, Wand const&  wnd) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::wand)
{data.wand = wnd;}


GameItem::
GameItem(char const*  name_, Price  pri, char16_t const*  desc, Card const&  crd) noexcept:
name(name_),
price(pri),
description(desc),
kind(GameItemKind::card)
{data.card = crd;}


GameItem::
GameItem(char const*  name_, Price  pri, char16_t const*  desc, Water const&  wat) noexcept:
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
  GameItem("きのぼう"        ,Price(0),u"",Sword(0)),
  GameItem("きんぞくのぼう"  ,Price(0),u"",Sword(0)),
  GameItem("せいどうのつるぎ",Price(0),u"",Sword(0)),
  GameItem("てつのつるぎ"    ,Price(0),u"",Sword(0)),
  GameItem("はがねのつるぎ"  ,Price(0),u"",Sword(0)),
  GameItem("ぎんのつるぎ"    ,Price(0),u"",Sword(0)),
  GameItem("みょうおうのつるぎ",Price(0),u"",Sword(0)),
  GameItem("きのたて",Price(0),u"",Shield(0)),
  GameItem("かわのたて",Price(0),u"",Shield(0)),
  GameItem("てつのたて",Price(0),u"",Shield(0)),
  GameItem("はがねのたて",Price(0),u"",Shield(0)),
  GameItem("やすいおび",Price(0),u"",Belt()),
  GameItem("ふつうのおび",Price(0),u"",Belt()),
  GameItem("こうきゅうおび",Price(0),u"",Belt()),
  GameItem("まよけのおび",Price(0),u"",Belt()),
  GameItem("ちからのおび",Price(0),u"",Belt()),
  GameItem("くろおび",Price(0),u"",Belt()),
  GameItem("こううんのおび",Price(0),u"",Belt()),
  GameItem("ふこうのおび",Price(0),u"",Belt()),
  GameItem("ねむりのつえ",Price(0),u"",Wand()),
  GameItem("どくのつえ",Price(0),u"",Wand()),
  GameItem("ふういんのつえ",Price(0),u"",Wand()),
  GameItem("てんいのつえ",Price(0),u"",Wand()),
  GameItem("いれかえのつえ",Price(0),u"",Wand()),
  GameItem("ほのおのつえ",Price(0),u"",Wand()),
  GameItem("つちのつえ",Price(0),u"",Wand()),
  GameItem("こんらんのつえ",Price(0),u"",Wand()),
  GameItem("くらやみのつえ",Price(0),u"",Wand()),
  GameItem("へんげのつえ",Price(0),u"",Wand()),
  GameItem("げんえいのつえ",Price(0),u"",Wand()),
  GameItem("ちからのふだ",Price(0),u"",Card()),
  GameItem("まもりのふだ",Price(0),u"",Card()),
  GameItem("こうてつのふだ",Price(0),u"",Card()),
  GameItem("だっしゅつのふだ",Price(0),u"",Card()),
  GameItem("いやしのみず",Price(0),u"",Water()),
  GameItem("いのちのみず",Price(0),u"",Water()),
  GameItem("どくのみず",Price(0),u"",Water()),
  GameItem("げどくのみず",Price(0),u"",Water()),
  GameItem("きよめのみず",Price(0),u"",Water()),
  GameItem("ただのみず",Price(0),u"",Water()),
  GameItem("くさいのみず",Price(0),u"",Water()),
  GameItem("きせきのみず",Price(0),u"",Water()),
};


size_t const
game_item_total = sizeof(game_item_table)/sizeof(GameItem);


}




