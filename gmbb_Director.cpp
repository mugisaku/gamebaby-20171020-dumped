#include"gmbb_Director.hpp"
#include<cstdio>




namespace gmbb{




void
Director::
set_script(char const*  s)
{
  using namespace gmbb::script;

  Element  el;

  StreamReader  r(s);

  TokenString  toks(r);

  ElementList  els;

    try
    {
      els = script::read_element_list(toks);
    }


    catch(StreamError const&  err)
    {
      err.print();

      return;
    }


  script_current = nullptr;
  script_end     = nullptr;

    for(auto&  e: els)
    {
        if(e.name == "script")
        {
          script_root = std::move(e);

          script_current = script_root.elements.data();

          script_end = script_current+script_root.elements.size();

          break;
        }
    }
}




void
Director::
insert_to_first(Actor&  target) noexcept
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
Director::
insert_to_last(Actor&  target) noexcept
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
Director::
remove(Actor&  target) noexcept
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
Director::
update() noexcept
{
  Actor::update();

    if(script_current && script_processor)
    {
        while(script_current != script_end)
        {
          script_processor(*this,*script_current++);
        }
    }


  auto  next = first;

    while(next)
    {
      next->update();

      next = next->get_next();
    }
}


void
Director::
render(Image&  dst, Point  offset) const noexcept
{
  auto  next = first;

  offset += get_relative_point();

    while(next)
    {
      next->render(dst,offset);

      next = next->get_next();
    }
}


covered_ptr<Actor>
Director::
find_by_name(std::string const&  name_) const noexcept
{
  auto  next = first;

    while(next)
    {
        if(next->is_director())
        {
          covered_ptr<Director>  subdir(next);

          auto  res = subdir->find_by_name(name_);

            if(res)
            {
              return res;
            }
        }

      else
        if(next->get_name() == name_)
        {
          return next;
        }


      next = next->get_next();
    }


  return nullptr;
}


void
Director::
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




