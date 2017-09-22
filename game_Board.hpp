#ifndef game_Board_HPP
#define game_Board_HPP


#include"game_Square.hpp"
#include"covered_ptr"
#include<vector>


namespace game{


constexpr int  board_width  = 256;
constexpr int  board_height = 256;


class Piece;


class
Board
{
  std::vector<Piece*>  pointer_hunger;

  std::vector<covered_ptr<Piece>>  piece_stock;

  Square  square_table[board_height][board_width];

  covered_ptr<Piece>  hero_piece;

  covered_ptr<Piece>  first;
  covered_ptr<Piece>   last;

  int  number_of_pieces=0;

public:
  Board() noexcept;
 ~Board();

  covered_ptr<Piece>  new_piece(int  x, int  y) noexcept;
  void                delete_piece(covered_ptr<Piece>  p) noexcept;

  Square&        get_square(      int  x, int  y)       noexcept{return square_table[y][x];}
  Square const&  get_square_const(int  x, int  y) const noexcept{return square_table[y][x];}

  void                set_hero_piece(covered_ptr<Piece>  p) noexcept{hero_piece = p;}
  covered_ptr<Piece>  get_hero_piece() const noexcept{return hero_piece;}

};


class
PieceLink
{
  friend Board;

  covered_ptr<Piece>  previous;
  covered_ptr<Piece>      next;

};


}




#endif




