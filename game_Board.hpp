#ifndef game_Board_HPP
#define game_Board_HPP


#include"gmbb_Director.hpp"
#include"game_Square.hpp"
#include"game_Piece.hpp"


namespace gmbb{


constexpr int  board_width  = 14;
constexpr int  board_height = 14;


constexpr int  board_image_width  = square_size*board_width ;
constexpr int  board_image_height = square_size*board_height;


class
Board: public Director
{
  std::vector<Piece*>  hunger;

  Square  square_table[board_height][board_width];

  void  link() noexcept;

public:
  Board() noexcept{link();}


  void  clear_all_distance() noexcept;

  covered_ptr<Piece>  new_piece(int  x, int  y) noexcept;

  void  delete_piece(covered_ptr<Piece>  p) noexcept;


  Square const*  get_square_begin() const noexcept{return &square_table[             0][          0];}
  Square const*    get_square_end() const noexcept{return &square_table[board_height-1][board_width];}

  Square&        get_square(      int  x, int  y)       noexcept{return square_table[y][x];}
  Square const&  get_square_const(int  x, int  y) const noexcept{return square_table[y][x];}

};


}




#endif




