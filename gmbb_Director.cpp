#include"gmbb_Director.hpp"
#include<cstdio>




namespace gmbb{




void
Director::
set_script(std::string const&  s) noexcept
{
  pointer = s.data()         ;
      end = s.data()+s.size();

  line_number = 1;
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

  auto  next = first;

    while(next)
    {
      next->update();

      next = next->get_next();
    }
}


void
Director::
render(Image&  dst, Point  dst_point) const noexcept
{
  auto  next = first;

    while(next)
    {
      next->render(dst,dst_point+next->get_relative_point());

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




