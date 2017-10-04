#include"game_SackItem.hpp"




namespace gmbb{




bool
SackItem::
operator<(SackItem const&  rhs) const noexcept
{
    if(pointer)
    {
        if(rhs.pointer)
        {
            if(( is_equipped() &&  rhs.is_equipped()) ||
               (!is_equipped() && !rhs.is_equipped()))
            {
              return (pointer < rhs.pointer);
            }


          return is_equipped();
        }


      return true;
    }


  return false;
}



}




