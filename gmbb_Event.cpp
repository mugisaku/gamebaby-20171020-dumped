#include"gmbb_Event.hpp"




namespace gmbb{


Event::
Event(TalkEvent const&  talk) noexcept:
kind(EventKind::talk)
{
  data.talk = talk;
}


}




