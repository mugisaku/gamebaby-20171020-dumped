#ifndef gmbb_ProtoBoard_HPP
#define gmbb_ProtoBoard_HPP


#include"gmbb_GadgetContainer.hpp"
#include"gmbb_SquareBase.hpp"
#include"gmbb_PieceBase.hpp"
#include"covered_ptr"
#include<vector>


namespace gmbb{


constexpr int  board_width  = 14;
constexpr int  board_height = 14;


constexpr int  board_image_width  = square_size*board_width ;
constexpr int  board_image_height = square_size*board_height;


template<typename  SQUARE, typename  PIECE>
class
ProtoBoard: public GadgetContainer
{
  std::vector<PIECE*>  pointer_hunger;

  std::vector<covered_ptr<PIECE>>  piece_stock;

  SQUARE  square_table[board_height][board_width];

  covered_ptr<PIECE>  hero_piece;

public:
  ProtoBoard() noexcept
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


  covered_ptr<PIECE>  new_piece(int  x, int  y) noexcept
  {
    auto&  sq = get_square(x,y);

      if(sq.get_piece())
      {
        return nullptr;
      }


    covered_ptr<PIECE>  p;

      if(piece_stock.size())
      {
        p = piece_stock.back();
        piece_stock.pop_back();
      }

    else
      {
        auto  raw_p = new PIECE(*this);

        pointer_hunger.emplace_back(raw_p);

        p = raw_p;
      }


    insert_to_last(*p);

    sq.set_piece(p);

    p->set_square(&sq);

    p->set_direction(Direction::front);

    p->update();

    return p;
  }


  void  delete_piece(covered_ptr<PIECE>  p) noexcept
  {
      if(p)
      {
        remove(*p);

        piece_stock.emplace_back(p);
      }
  }


  SQUARE const*  get_square_begin() const noexcept{return &square_table[             0][          0];}
  SQUARE const*    get_square_end() const noexcept{return &square_table[board_height-1][board_width];}

  SQUARE&        get_square(      int  x, int  y)       noexcept{return square_table[y][x];}
  SQUARE const&  get_square_const(int  x, int  y) const noexcept{return square_table[y][x];}

  void                set_hero_piece(covered_ptr<PIECE>  p)       noexcept{       hero_piece = p;}
  covered_ptr<PIECE>  get_hero_piece(                     ) const noexcept{return hero_piece    ;}

  void  step() const noexcept
  {
    auto  next = get_first();

      while(next)
      {
        next->update();

        next = next->get_next();
      }
  }

};


}




#endif




