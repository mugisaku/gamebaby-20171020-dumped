#include"gmbb_TaskList.hpp"


namespace gmbb{
namespace task_list{


namespace{


covered_ptr<Task>  first;
covered_ptr<Task>   last;


}




void
push(Task&  t) noexcept
{
    if(last)
    {
      last->connect(t);
      last = &t;
    }

  else
    {
      first = &t;
       last = &t;
    }
}


void
erase(Task&  t) noexcept
{
    if(first == &t)
    {
      first = first->get_next();
    }


    if(last == &t)
    {
      last = last->get_previous();
    }


  t.disconnect();
}


void
update() noexcept
{
  auto  current = first;

    while(current)
    {
      current->update();

      current = current->get_next();
    }
}


void
render(Image&  dst, Point  offset) noexcept
{
    if(first)
    {
      auto  current = first.get_const_raw_pointer();

        while(current)
        {
          current->render(dst,offset);

          current = current->get_const_next();
        }
    }
}




}}




