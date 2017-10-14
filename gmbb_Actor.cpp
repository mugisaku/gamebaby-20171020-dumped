#include"gmbb_Actor.hpp"
#include"gmbb_Director.hpp"
#include<cstdlib>




namespace gmbb{




void
Actor::
enter_into_group(Director&  director_, Point  point) noexcept
{
    if(!director)
    {
      director = &director_;

      relative_point = point;

      notify_needing_to_redraw();

      director->insert_to_last(*this);
    }
}


void
Actor::
exit_from_group() noexcept
{
    if(director)
    {
      notify_needing_to_redraw();

      director->remove(*this);

      director = nullptr;
    }
}




void
Actor::
connect(Actor&  a, Actor&  b) noexcept
{
  a.next     = &b;
  b.previous = &a;
}
	

void
Actor::
disconnect() noexcept
{
    if(previous)
    {
      previous->next = next;
    }


    if(next)
    {
      next->previous = previous;
    }


  previous = nullptr;
      next = nullptr;
  director = nullptr;
}




void
Actor::
notify_needing_to_redraw() noexcept
{
  needing_to_redraw = true;

    if(director && !director->is_needing_to_redraw())
    {
      director->notify_needing_to_redraw();
    }
}


void
Actor::
move_relative_point(int  x, int  y) noexcept
{
  relative_point.x += x;
  relative_point.y += y;
}


void
Actor::
update() noexcept
{
    if(exectx.is_finished())
    {
       if(number_of_actions)
       {
         exectx.decode(action_buffer[reading_index++]);

           if(reading_index >= buffer_size)
           {
             reading_index = 0;
           }


         --number_of_actions;
       }
    }

  else
    {
      exectx.step(*this);
    }
}




}




