#include"game_Square.hpp"
#include"game_Piece.hpp"




namespace gmbb{


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




