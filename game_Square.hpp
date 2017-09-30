#ifndef game_Square_HPP
#define game_Square_HPP


#include"game_Sack.hpp"
#include"game_Direction.hpp"
#include"game_Trap.hpp"
#include"covered_ptr"


namespace game{


enum class
SquareKind
{
  null,
  wall,
  room,
  corridor,

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


constexpr int  square_size = 24;


class
Square
{
  int  x;
  int  y;

  SquareLinkSet  linkset;

  SquareKind  kind=SquareKind::null;

  SackItem  item;

  covered_ptr<Piece>  piece_ptr;

  Trap  trap;

public:
  bool  operator==(SquareKind  k) const noexcept{return kind == k;}
  bool  operator!=(SquareKind  k) const noexcept{return kind != k;}

  void  reset(int  x_, int  y_, SquareLinkSet const&  linkset_) noexcept;

  int  get_x() const noexcept{return x;}
  int  get_y() const noexcept{return y;}

  SquareLinkSet&  get_linkset() noexcept{return linkset;}

  SquareKind  get_kind(             ) const noexcept{return kind    ;}
  void        set_kind(SquareKind  k)       noexcept{       kind = k;}

  covered_ptr<Square>  operator[](Direction  d) const noexcept{return linkset.get(d);}


  covered_ptr<Piece>  get_piece(                     ) const noexcept{return piece_ptr    ;}
  void                set_piece(covered_ptr<Piece>  p)       noexcept{       piece_ptr = p;}


  void  set_item(SackItem const&  i) noexcept{item = i;}

  SackItem&        get_item()       noexcept{return item;}
  SackItem const&  get_item() const noexcept{return item;}

  bool  can_put_item() const noexcept{return !item && !trap;}


  void         set_trap(Trap const&  tr)       noexcept{       trap = tr;}
  Trap const&  get_trap(               ) const noexcept{return trap     ;}


  void  remove_piece() noexcept;

};


}




#endif




