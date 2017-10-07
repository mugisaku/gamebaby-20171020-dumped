#ifndef gmbb_SquareBase_HPP
#define gmbb_SquareBase_HPP


#include"gmbb_Direction.hpp"
#include"covered_ptr"


namespace gmbb{


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


using distance_t = uint32_t;


class
SquareBase
{
  int  x;
  int  y;

protected:
  SquareLinkSet  linkset;

  covered_ptr<Piece>  piece_ptr;

  distance_t  distance=0;

  int  mpp_value;//mpp is MultiPurPose

public:
  void  reset(int  x_, int  y_, SquareLinkSet const&  linkset_) noexcept;

  int  get_x() const noexcept{return x;}
  int  get_y() const noexcept{return y;}

  SquareLinkSet&  get_linkset() noexcept{return linkset;}

  covered_ptr<Square>  operator[](Direction  d) const noexcept{return linkset.get(d);}


  void  remove_piece() noexcept;

  covered_ptr<Piece>  get_piece(                     ) const noexcept{return piece_ptr    ;}
  void                set_piece(covered_ptr<Piece>  p)       noexcept{       piece_ptr = p;}

  void  set_mpp_value(int  v)       noexcept{       mpp_value = v;}
  int   get_mpp_value(      ) const noexcept{return mpp_value    ;}

  void         set_distance(distance_t  d)       noexcept{       distance = d;}
  distance_t   get_distance(             ) const noexcept{return distance    ;}

};


}




#endif




