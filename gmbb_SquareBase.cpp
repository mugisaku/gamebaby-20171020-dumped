#include"gmbb_SquareBase.hpp"




namespace gmbb{




void
SquareBase::
reset(int  x_, int  y_, SquareLinkSet const&  linkset_) noexcept
{
  x = x_;
  y = y_;

  linkset = linkset_;
}



}




