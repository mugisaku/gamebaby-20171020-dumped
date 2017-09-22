#ifndef game_Square_HPP
#define game_Square_HPP


#include"game_GameItem.hpp"
#include"covered_ptr"


namespace game{


enum class
Direction
{
        front,
   front_left,
         left,
    back_left,
         back,
   back_right,
        right,
  front_right,

};


enum class
TrapKind
{
  null,
  
};


enum class
SquareKind
{
  null,
  floor,
  wall,
  breakable_wall,
  
};


class Square;
class Piece;


class
SquareLinkSet
{
  covered_ptr<Square>  table[8];

public:
  void                 set(Direction  d, covered_ptr<Square>  sq)       noexcept{       table[static_cast<int>(d)] = sq;}
  covered_ptr<Square>  get(Direction  d                         ) const noexcept{return table[static_cast<int>(d)]     ;}

};


class
Square
{
  int  x;
  int  y;

  SquareLinkSet  linkset;

  SquareKind  kind=SquareKind::null;

  GameItem const*      item_ptr=nullptr;
  covered_ptr<Piece>  piece_ptr;

  TrapKind  trap_kind=TrapKind::null;

  int  trap_value=0;

public:
  void  reset(int  x_, int  y_, SquareLinkSet const&  linkset_) noexcept;

  int  get_x() const noexcept{return x;}
  int  get_y() const noexcept{return y;}

  SquareLinkSet&  get_linkset() noexcept{return linkset;}

  SquareKind  get_kind() const noexcept{return kind;}

  TrapKind  get_trap_kind() const noexcept{return trap_kind;}

  int  get_trap_value() const noexcept{return trap_value;}

  covered_ptr<Square>  operator[](Direction  d) const noexcept{return linkset.get(d);}

  void  change_piece(covered_ptr<Piece>  p) noexcept{piece_ptr = p;}

  covered_ptr<Piece>  get_piece() const noexcept{return piece_ptr;}
  GameItem const*      get_item() const noexcept{return  item_ptr;}

  void  remove_piece() noexcept;

};


}




#endif




