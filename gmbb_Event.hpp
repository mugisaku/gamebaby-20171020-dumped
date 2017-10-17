#ifndef GMBB_Event_HPP
#define GMBB_Event_HPP


#include"covered_ptr"


namespace gmbb{


enum class
EventKind
{
  null,
  talk,

};


class Actor;


struct
TalkEvent
{
  covered_ptr<Actor>   host;
  covered_ptr<Actor>  guest;

};


union
EventData
{
  TalkEvent  talk;

   EventData(){}
  ~EventData(){}
};


class
Event
{
  EventKind  kind=EventKind::null;
  EventData  data;

public:
  Event() noexcept{}
  Event(TalkEvent const&  talk) noexcept;

  EventKind  get_kind() const noexcept{return kind;}

  EventData const*  operator->() const noexcept{return &data;}

};


}




#endif




