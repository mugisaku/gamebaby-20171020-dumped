#include"gmbb_EventQueue.hpp"


namespace gmbb{
namespace EventQueue{


namespace{


struct
Node
{
  Event  event;

  Node*  next=nullptr;

  Node(Event const&  evt): event(evt){}

};


Node*  first=nullptr;
Node*   last=nullptr;

int  number=0;


}




void
push_event(Event  evt) noexcept
{
  auto  nd = new Node(evt);

    if(last)
    {
      last->next = nd;
      last = nd;
    }

  else
    {
      first = nd;
       last = nd;
    }


  ++number;
}


Event
pop_event() noexcept
{
  Event  evt = first->event;

  auto  next = first->next;

  delete first       ;
         first = next;

  --number;

    if(!first)
    {
      last = nullptr;
    }


  return evt;
}


int
get_number_of_events() noexcept
{
  return number;
}




}}




