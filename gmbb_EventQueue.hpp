#ifndef GMBB_EventQueue_HPP
#define GMBB_EventQueue_HPP


#include"gmbb_Event.hpp"


namespace gmbb{
namespace EventQueue{


void  push_event(Event  evt) noexcept;

template<typename...  ARGS>
void
push_event(ARGS...  args) noexcept
{
  push_event(Event(args...));
}


Event  pop_event() noexcept;

int  get_number_of_events() noexcept;


}}




#endif




