#ifndef game_hero_HPP
#define game_hero_HPP


#include"game_Sack.hpp"


namespace game{


class
Hero
{
  char16_t*  name;

  int  damage_totality=0;

  int  barehand_level=0;

  int   sword_handling_level=0;
  int  shield_handling_level=0;

  Sack  sack;

public:
  Hero();

  char16_t const*  get_name() const noexcept{return name;}

  Sack&  get_sack() noexcept{return sack;}

};


}




#endif




