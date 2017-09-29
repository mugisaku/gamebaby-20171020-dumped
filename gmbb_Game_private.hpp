#ifndef GMBB_Game_private_HPP
#define GMBB_Game_private_HPP


#include"gmbb.hpp"
#include"gmbb_IntervalTimer.hpp"
#include"game_Piece.hpp"
#include"game_Board.hpp"
#include"game_Sack.hpp"
#include<initializer_list>


namespace gmbb{


constexpr int  screen_width  = 320;
constexpr int  screen_height = 240;

constexpr int  square_size = 24;

constexpr int  board_image_w = (square_size*game::board_width );
constexpr int  board_image_h = (square_size*game::board_height);


extern
game::Hero
hero;


extern
covered_ptr<game::Piece>
hero_piece;


extern
game::Board
board;


extern
Image
screen_image;


extern
Image
character_image;


extern IntervalTimer
interval_timer;


extern
GlyphSet
glset;


extern
GlyphSet
large_glset;


extern
Widget
root_widget;




void  move_hero_piece_to_forward();
void  turn_hero_piece_to_left();
void  turn_hero_piece_to_right();
void  move_hero_piece_to_backward();


void  move_board_view(int  x, int  y) noexcept;

void  show_board_view() noexcept;
void  hide_board_view() noexcept;
void  update_board_view() noexcept;

void  show_status_monitor() noexcept;
void  hide_status_monitor() noexcept;
void  update_status_monitor() noexcept;

void  show_status_reportor() noexcept;
void  hide_status_reportor() noexcept;
void  update_status_reportor() noexcept;


bool  is_status_monitor_window_opened() noexcept;
bool  is_status_report_window_opened()  noexcept;


void   open_main_menu_window() noexcept;
void  close_main_menu_window() noexcept;
void  start_main_menu() noexcept;
bool  is_main_menu_window_opened() noexcept;


void   open_sack_menu_window() noexcept;
void  close_sack_menu_window() noexcept;
void  start_sack_menu() noexcept;
bool  is_sack_menu_window_opened()      noexcept;


void  prepare_choosing_window(std::initializer_list<char16_t const*>  ls, Point  point) noexcept;
void   open_choosing_window() noexcept;
void  close_choosing_window() noexcept;
void    start_choosing(bool  cancelable=true) noexcept;
bool  is_choosing_window_opened()       noexcept;


void   open_message_window() noexcept;
void  close_message_window() noexcept;
void  start_message(char16_t const*  text) noexcept;
bool  is_message_window_opened()        noexcept;



void  update_piece(game::Piece&  p) noexcept;
void  render_piece(game::Piece const&  p, Image&  dst, Point  dst_point) noexcept;


}




#endif




