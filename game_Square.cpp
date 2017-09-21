#include"game_Square.hpp"
#include"game_Piece.hpp"




namespace game{




void
Square::
reset(int  x_, int  y_, SquareLinkSet const&  linkset_) noexcept
{
  x = x_;
  y = y_;

  linkset = linkset_;

   item_ptr = nullptr;
  piece_ptr = nullptr;
}


void
Square::
remove_piece() noexcept
{
    if(piece_ptr)
    {
      auto&  brd = piece_ptr->get_board();

      brd.delete_piece(piece_ptr);

      piece_ptr = nullptr;
    }
}



}




