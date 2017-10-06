#include"gmbb_GadgetContainer.hpp"
#include<cstdio>




namespace gmbb{




void
GadgetContainer::
insert_to_first(Gadget&  target) noexcept
{
    if(first)
    {
      target.connect_to_previous(*first);

      first = &target;
    }

  else
    {
      first = &target;
       last = &target;
    }
}


void
GadgetContainer::
insert_to_last(Gadget&  target) noexcept
{
    if(last)
    {
      target.connect_to_next(*last);

      last = &target;
    }

  else
    {
      first = &target;
       last = &target;
    }
}


void
GadgetContainer::
remove(Gadget&  target) noexcept
{
    if(this->first == &target)
    {
      this->first = target.get_next();
    }


    if(this->last == &target)
    {
      this->last = target.get_previous();
    }


  target.disconnect();
}


void
GadgetContainer::
update() noexcept
{
  Gadget::update();

  auto  next = first;

    while(next)
    {
      next->update();

      next = next->get_next();
    }
}


void
GadgetContainer::
render(Image&  dst, Point  dst_point) const noexcept
{
  auto  next = first;

    while(next)
    {
      next->render(dst,dst_point+next->get_relative_point());

      next = next->get_next();
    }
}


void
GadgetContainer::
print() const noexcept
{
  auto  next = first.get_const_raw_pointer();

    while(next)
    {
      next->print();

      printf(",");

      next = next->get_const_next();
    }
}


}




