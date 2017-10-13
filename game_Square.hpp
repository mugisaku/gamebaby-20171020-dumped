#ifndef game_Square_HPP
#define game_Square_HPP


#include"gmbb.hpp"
#include"game_Sack.hpp"
#include"game_Trap.hpp"




namespace gmbb{


constexpr int  square_size = 24;


enum class
SquareKind
{
  null,
  wall,
  room,
};


class
SquareLinkSet
{
  covered_ptr<Square>  table[8];

public:
  void                 set(Direction  d, covered_ptr<Square>  sq)       noexcept{       table[static_cast<int>(d)] = sq;}
  covered_ptr<Square>  get(Direction  d                         ) const noexcept{return table[static_cast<int>(d)]     ;}

};


class
Square: public SquareBase
{
  SquareKind  kind=SquareKind::null;

  SquareLinkSet  linkset;

  SackItem  item;

  Trap  trap;

public:
  bool  operator==(SquareKind  k) const noexcept{return kind == k;}
  bool  operator!=(SquareKind  k) const noexcept{return kind != k;}

  SquareKind  get_kind(             ) const noexcept{return kind    ;}
  void        set_kind(SquareKind  k)       noexcept{       kind = k;}


  void  reset(int  x, int  y, SquareLinkSet&  lnset) noexcept;

  SquareLinkSet&  get_linkset() noexcept{return linkset;}

  covered_ptr<Square>         operator[](Direction  d) const noexcept{return linkset.get(d);}
  covered_ptr<Square>  get_linked_square(Direction  d) const noexcept{return linkset.get(d);}


  void                 set_item(SackItem const&  i               ) noexcept{item = i;}
  covered_ptr<Square>  put_item(SackItem const&  i, distance_t  d) noexcept;

  SackItem&        get_item()       noexcept{return item;}
  SackItem const&  get_item() const noexcept{return item;}

  bool  can_put_item() const noexcept{return (kind == SquareKind::room) && !item && !trap;}

  void         set_trap(Trap const&  tr)       noexcept{       trap = tr;}
  Trap const&  get_trap(               ) const noexcept{return trap     ;}


  void  remove_piece() noexcept;

};


}




#endif




