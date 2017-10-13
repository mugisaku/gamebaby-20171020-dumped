#ifndef GMBB_Director_HPP
#define GMBB_Director_HPP


#include"gmbb_Actor.hpp"
#include"gmbb_Script__Element.hpp"


namespace gmbb{


class Board;


class
Director: public Actor
{
  using ScriptProcessor = void(*)(Director&  di, script::Element const&  e);

  covered_ptr<Board>  board;

  covered_ptr<Actor>  first;
  covered_ptr<Actor>   last;

  script::Element  script_root;

  script::Element const*  script_current=nullptr;
  script::Element const*  script_end    =nullptr;

  ScriptProcessor  script_processor=nullptr;

  void  process_new(      script::ElementList const&  ls) noexcept;
  void  process_new_piece(script::ElementList const&  ls) noexcept;

public:
  Director() noexcept{}
  Director(Board&  brd) noexcept: board(&brd){}

  void  set_script(char const*  s);

  void  set_script_processor(ScriptProcessor  scproc) noexcept{script_processor = scproc;}

  void  insert_to_first(Actor&  target) noexcept;
  void  insert_to_last( Actor&  target) noexcept;

  void  remove(Actor&  target) noexcept;

  covered_ptr<Actor>  get_first() const noexcept{return first;}
  covered_ptr<Actor>  get_last()  const noexcept{return  last;}

  Actor const*  get_const_first() const noexcept{return first.get_const_raw_pointer();}
  Actor const*  get_const_last()  const noexcept{return  last.get_const_raw_pointer();}

  void  update() noexcept override;

  void  render(Image&  dst, Point  offset) const noexcept override;

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




