#ifndef gmbb_PieceBase_HPP
#define gmbb_PieceBase_HPP


#include"gmbb_EffectObject.hpp"


namespace gmbb{


class Square;


class
PieceBase: public EffectObject
{
protected:
  covered_ptr<Square>  square;

public:
  PieceBase() noexcept{}

  PieceBase(PieceBase const&  rhs) noexcept=delete;
  PieceBase(PieceBase&&       rhs) noexcept=delete;

  PieceBase&  operator=(PieceBase const&  rhs) noexcept=delete;
  PieceBase&  operator=(PieceBase&&       rhs) noexcept=delete;

  void                 set_square(covered_ptr<Square>  sq)       noexcept{       square = sq;}
  covered_ptr<Square>  get_square(                       ) const noexcept{return square     ;}

};


}




#endif




