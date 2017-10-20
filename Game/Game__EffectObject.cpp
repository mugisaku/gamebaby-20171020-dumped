#include"Game_private.hpp"


namespace gmbb{


namespace{


constexpr int  number_of_objects = 80;


EffectObject
object_array[number_of_objects];


covered_ptr<EffectObject>
stock[number_of_objects];


int
index;


covered_ptr<EffectObject>  first;
covered_ptr<EffectObject>   last;


}


covered_ptr<EffectObject>
new_effect_object()
{
  static bool  initialized;

    if(!initialized)
    {
      auto  p = &stock[0];

        for(auto&  o: object_array)
        {
          *p++ = &o;
        }


      initialized = true;
    }


  auto  p = stock[index++];

    if(last)
    {
      last->connect(*p);

      last = p;
    }

  else
    {
      first = p;
       last = p;
    }


  return p;
}


void
delete_effect_object(covered_ptr<EffectObject>  fo)
{
    if(fo)
    {
      auto  previous = fo->get_previous();
      auto      next = fo->get_next();

      fo->disconnect();

        if(fo == first)
        {
          first = next;
        }


        if(fo == last)
        {
          last = previous;
        }


      stock[--index] = fo;
    }
}


bool
has_active_effect_object()
{
  return first;
}


void
update_effect()
{
  auto  next = first;

    while(next)
    {
      next->update();

      next = next->get_next();
    }
}


void
render_effect()
{
  auto  next = first;

    while(next)
    {
        if(next->check_visible_count())
        {
          next->render(screen_image,-board.get_view_point());
        }


      next = next->get_next();
    }
}


}




