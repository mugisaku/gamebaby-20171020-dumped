#include"game_Board.hpp"
#include"game_Piece.hpp"


namespace game{




Board::
Board() noexcept
{
  SquareLinkSet  linkset;

    for(int  y = 0;  y < board_height;  ++y){
    for(int  x = 0;  x < board_width ;  ++x){
      auto const   is_left_available = (x                   );
      auto const  is_right_available = (x < (board_width -1));
      auto const   is_back_available = (y                   );
      auto const  is_front_available = (y < (board_height-1));

      linkset.set(Direction::left      ,(                      is_left_available)? &square_table[y  ][x-1]:nullptr);
      linkset.set(Direction::back_left ,( is_back_available && is_left_available)? &square_table[y-1][x-1]:nullptr);
      linkset.set(Direction::front_left,(is_front_available && is_left_available)? &square_table[y+1][x-1]:nullptr);

      linkset.set(Direction::right      ,(                      is_right_available)? &square_table[y  ][x+1]:nullptr);
      linkset.set(Direction::back_right ,( is_back_available && is_right_available)? &square_table[y-1][x+1]:nullptr);
      linkset.set(Direction::front_right,(is_front_available && is_right_available)? &square_table[y+1][x+1]:nullptr);


      square_table[y][x].reset(x,y,linkset);
    }}
}


Board::
~Board()
{
    for(auto  ptr: pointer_hunger)
    {
      delete ptr;
    }
}




covered_ptr<Piece>
Board::
new_piece(int  x, int  y) noexcept
{
  auto&  sq = get_square(x,y);

    if(sq.get_piece())
    {
      return nullptr;
    }


  covered_ptr<Piece>  p;

    if(piece_stock.size())
    {
      p = piece_stock.back();
      piece_stock.pop_back();
    }

  else
    {
      auto  raw_p = new Piece(*this);

      pointer_hunger.emplace_back(raw_p);

      p = raw_p;
    }


    if(last)
    {
      last->get_link().next = p;

      p->get_link().previous = last    ;
                               last = p;
    }

  else
    {
      first = p;
       last = p;
    }


  ++number_of_pieces;


  sq.change_piece(p);

  p->change_square(&sq);

  return p;
}


void
Board::
delete_piece(covered_ptr<Piece>  p) noexcept
{
    if(p)
    {
      auto&  ln = p->get_link();

        if(ln.previous){ln.previous->get_link().next = ln.next;}
        if(ln.next){ln.next->get_link().previous = ln.previous;}

      ln.previous = nullptr;
      ln.next     = nullptr;

        if(first == p)
        {
          first = ln.next;
        }


        if(last == p)
        {
          last = ln.previous;
        }


      piece_stock.emplace_back(p);

      --number_of_pieces;
    }
}




}




