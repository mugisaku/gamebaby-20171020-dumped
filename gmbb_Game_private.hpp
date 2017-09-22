#ifndef GMBB_Game_private_HPP
#define GMBB_Game_private_HPP


#include"gmbb.hpp"
#include"game_Piece.hpp"
#include"game_Board.hpp"
#include"game_Sack.hpp"
#include<initializer_list>


namespace gmbb{


constexpr int  screen_width  = 320;
constexpr int  screen_height = 240;


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


using Routine = void(*)(Controller const&  ctrl) noexcept;

void  push_routine(Routine  r) noexcept;
void   pop_routine(          ) noexcept;




void  move_board_view_to_up();
void  move_board_view_to_left();
void  move_board_view_to_right();
void  move_board_view_to_down();

void  show_board_view() noexcept;
void  hide_board_view() noexcept;
void  update_board_view() noexcept;

void  show_status_monitor() noexcept;
void  hide_status_monitor() noexcept;
void  update_status_monitor() noexcept;

void  show_status_reportor() noexcept;
void  hide_status_reportor() noexcept;
void  update_status_reportor() noexcept;

void  start_main_menu() noexcept;
void  start_sack_menu() noexcept;
void    start_message(char16_t const*  text) noexcept;
void    start_choosing(std::initializer_list<char16_t const*>  ls, Point  point, bool  cancelable=true) noexcept;


void  set_response(int  v) noexcept;
int   get_response(      ) noexcept;



}




#endif




