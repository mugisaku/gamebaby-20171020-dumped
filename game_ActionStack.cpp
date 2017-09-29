#include"game_ActionStack.hpp"
#include<cstdio>


namespace game{




void
ActionStack::
push(Action::Callback  cb, int  count) noexcept
{
  array[index++] = Action(cb,count);
}


void
ActionStack::
pop() noexcept
{
  --index;
}


void
ActionStack::
operator()(Piece&  p) noexcept
{
START:
//printf("%d\n",index);
    if(index)
    {
      auto&  act = array[index-1];

        if(!act.count)
        {
          pop();

          goto START;
        }

      else
        {
          act.callback(p,--act.count);
        }
    }
}


}




