#include"game_Board.hpp"


namespace gmbb{




void
Board::
link() noexcept
{
  SquareLinkSet  linkset;

    for(int  y = 0;  y < board_height;  ++y){
    for(int  x = 0;  x < board_width ;  ++x){
      auto const   is_left_available = (x                   );
      auto const  is_right_available = (x < (board_width- 1));
      auto const   is_back_available = (y                   );
      auto const  is_front_available = (y < (board_height-1));

      linkset.set(Direction::front,is_front_available? &get_square(x,y+1):nullptr);
      linkset.set(Direction::back , is_back_available? &get_square(x,y-1):nullptr);

      linkset.set(Direction::left      ,(                      is_left_available)? &get_square(x-1,y  ):nullptr);
      linkset.set(Direction::back_left ,( is_back_available && is_left_available)? &get_square(x-1,y-1):nullptr);
      linkset.set(Direction::front_left,(is_front_available && is_left_available)? &get_square(x-1,y+1):nullptr);

      linkset.set(Direction::right      ,(                      is_right_available)? &get_square(x+1,y  ):nullptr);
      linkset.set(Direction::back_right ,( is_back_available && is_right_available)? &get_square(x+1,y-1):nullptr);
      linkset.set(Direction::front_right,(is_front_available && is_right_available)? &get_square(x+1,y+1):nullptr);


      get_square(x,y).reset(x,y,linkset);
    }}
}


void
Board::
clear_all_distance() noexcept
{
  Square*  p = &square_table[0][0];

    for(int  i = 0;  i < (board_width*board_height);  ++i)
    {
      p[i].set_distance(0);
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

    if(hunger.size())
    {
      p = hunger.back();
      hunger.pop_back();
    }

  else
    {
      auto  raw_p = new Piece(*this);

      hunger.emplace_back(raw_p);

      p = raw_p;
    }


  insert_to_last(*p);

  sq.set_piece(p);

  p->set_square(&sq);

  p->set_direction(Direction::front);

  p->update();

  return p;
}


void
Board::
delete_piece(covered_ptr<Piece>  p) noexcept
{
    if(p)
    {
      remove(*p);

      hunger.emplace_back(&*p);
    }
}


}




