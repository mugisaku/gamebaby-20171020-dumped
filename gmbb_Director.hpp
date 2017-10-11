#ifndef GMBB_Director_HPP
#define GMBB_Director_HPP


#include"gmbb_Actor.hpp"


namespace gmbb{


class
Director: public Actor
{
  covered_ptr<Actor>  first;
  covered_ptr<Actor>   last;

  char const*  pointer=nullptr;
  char const*      end=nullptr;

  int  line_number=1;

  void  skip_spaces() noexcept;

public:
  void  set_script(std::string const&  s) noexcept;

  void  process_script() noexcept;

  void  insert_to_first(Actor&  target) noexcept;
  void  insert_to_last( Actor&  target) noexcept;

  void  remove(Actor&  target) noexcept;

  covered_ptr<Actor>  get_first() const noexcept{return first;}
  covered_ptr<Actor>  get_last()  const noexcept{return  last;}

  Actor const*  get_const_first() const noexcept{return first.get_const_raw_pointer();}
  Actor const*  get_const_last()  const noexcept{return  last.get_const_raw_pointer();}

  void  update() noexcept override;

  void  render(Image&  dst, Point  dst_point) const noexcept override;

  template<typename  T>
  void
  for_each(T&  t) const noexcept
  {
    auto  next = first;

      while(next)
      {
        t(*next);

        next = next->get_next();
      }
  }

  bool  is_director() const noexcept override{return true;}

  covered_ptr<Actor>  find_by_name(std::string const&  name_) const noexcept;

  void  print() const noexcept override;

};


}




#endif




