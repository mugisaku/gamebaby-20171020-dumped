#ifndef GMBB_Game_private_HPP
#define GMBB_Game_private_HPP


#include"gmbb.hpp"
#include"game_Piece.hpp"
#include"game_Board.hpp"
#include<initializer_list>


namespace gmbb{


extern
game::Hero
hero;


extern
game::Board
board;


extern
Image
screen_image;


extern
GlyphSet
glset;


extern
Widget
root_widget;




void  show_status_monitor() noexcept;
void  hide_status_monitor() noexcept;

void  start_main_menu() noexcept;
void  start_sack_menu() noexcept;
void    start_message(char16_t const*  text) noexcept;
void    start_choosing(std::initializer_list<char16_t const*>  ls, Point  point) noexcept;

bool  is_main_menu_active() noexcept;
bool  is_sack_menu_active() noexcept;
bool  is_message_active()   noexcept;
bool  is_choosing_active()   noexcept;

void    process_message(Controller const&  ctrl) noexcept;
void  process_main_menu(Controller const&  ctrl) noexcept;
void  process_sack_menu(Controller const&  ctrl) noexcept;
void  process_choosing(Controller const&  ctrl) noexcept;


void  set_response(int  v) noexcept;
int   get_response(      ) noexcept;



}




#endif




