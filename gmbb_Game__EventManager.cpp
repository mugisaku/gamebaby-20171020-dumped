#include"gmbb_Game_private.hpp"


namespace gmbb{


namespace{

struct
Node
{
  Event  event;

  Node*  next=nullptr;

  Node(Event const&  evt): event(evt){}

};


Node*  first;
Node*   last;

int  number;


Event
pop() noexcept
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


}


void
push_event(Event const&  evt) noexcept
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


int
get_number_of_events() noexcept
{
  return number;
}


void
clear_all_event() noexcept
{
    while(get_number_of_events())
    {
      pop();
    }
}


void
process_event() noexcept
{
    if(get_number_of_events())
    {
      Event  evt = pop();

        switch(evt.get_kind())
        {
      case(EventKind::talk):
        {
          static std::string const  none("none");

          auto  talk = find_talk(evt->talk.host->get_name(),evt->talk.guest? evt->talk.guest->get_name():none);

            if(talk)
            {
              start_message(talk->data());
            }
        }
          break;
        }
    }
}


}




