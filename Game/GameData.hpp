#ifndef GMBB_GameData_HPP
#define GMBB_GameData_HPP


#include"gmbb_Standard.hpp"
#include"GameItem.hpp"


namespace gmbb{


constexpr int  square_size = 24;

constexpr int  screen_width  = 320;
constexpr int  screen_height = 240;

constexpr int  board_width  = 14;
constexpr int  board_height = 14;

constexpr int  board_image_width  = square_size*board_width ;
constexpr int  board_image_height = square_size*board_height;

constexpr int  board_image_w = (square_size*board_width );
constexpr int  board_image_h = (square_size*board_height);


extern Image  character_image;


Rectangle  get_rectangle_for_item(GameItem const&  itm) noexcept;


}




#endif




