#include"gmbb_Gadget.hpp"
#include"gmbb_GadgetContainer.hpp"
#include<cstdlib>




namespace gmbb{




void
Gadget::
enter_into_container(GadgetContainer&  container_, Point  point) noexcept
{
    if(!container)
    {
      container = &container_;

      relative_point = point;

      notify_needing_to_redraw();

      container->insert_to_last(*this);
    }
}


void
Gadget::
exit_from_container() noexcept
{
    if(container)
    {
      notify_needing_to_redraw();

      container->remove(*this);

      container = nullptr;
    }
}




void
Gadget::
connect_to_previous(Gadget&  target) noexcept
{
  target.previous = this;

  next = &target;
}


void
Gadget::
connect_to_next(Gadget&  target) noexcept
{
  target.next = this;

  previous = &target;
}
	

void
Gadget::
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
  container = nullptr;
}




void
Gadget::
notify_needing_to_redraw() noexcept
{
  needing_to_redraw = true;

    if(container && !container->is_needing_to_redraw())
    {
      container->notify_needing_to_redraw();
    }
}


void
Gadget::
move_relative_point(int  x, int  y) noexcept
{
  relative_point.x += x;
  relative_point.y += y;
}


}




