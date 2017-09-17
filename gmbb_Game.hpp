#ifndef GMBB_Game_HPP
#define GMBB_Game_HPP


#include"gmbb.hpp"


namespace gmbb{


Image const&  get_screen_image() noexcept;

bool  is_screen_needing_to_redraw() noexcept;

void  initialize() noexcept;

void  step(Controller const&  ctrl);


}




#endif




