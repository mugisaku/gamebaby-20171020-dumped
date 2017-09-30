#include"game_Object.hpp"


namespace game{




void
Object::
reset_frame() noexcept
{
  frame_count = 0;
  frame_index = 0;
}


void
Object::
increase_frame_index_when_over(int  limit) noexcept
{
    if(frame_count >= limit)
    {
      frame_count  = 0;
      frame_index += 1;
    }
}


void
Object::
change_action_index(int  v) noexcept
{
  action_index = v;

  reset_frame();
}




void
Object::
link(covered_ptr<Object>  o) noexcept
{
  next = o;

    if(o)
    {
      o->previous = this;
    }
}


void
Object::
unlink() noexcept
{
    if(previous)
    {
      previous->next = next;

      previous = nullptr;
    }


    if(next)
    {
      next->previous = previous;

      next = nullptr;
    }
}




void
Object::
step() noexcept
{
  ++frame_count;

  update();
}




}




