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

      linkset.set(Direction::front,is_front_available? &square_table[y+1][x]:nullptr);
      linkset.set(Direction::back , is_back_available? &square_table[y-1][x]:nullptr);

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
      last->link(p);

      last = p;
    }

  else
    {
      first = p;
       last = p;
    }


  ++number_of_pieces;


  sq.set_piece(p);

  p->set_square(&sq);
  p->set_direction(Direction::front);

  p->set_rendering_point_by_current_square();

  return p;
}


void
Board::
delete_piece(covered_ptr<Piece>  p) noexcept
{
    if(p)
    {
      auto  previous = p->get_previous();
      auto      next = p->get_next();

        if(first == p)
        {
          first = next;
        }


        if(last == p)
        {
          last = previous;
        }


      piece_stock.emplace_back(p);

      --number_of_pieces;
    }
}


void
Board::
step() const noexcept
{
  auto  next = first;

    while(next)
    {
      next->step();

      next = next->get_next();
    }
}


}




