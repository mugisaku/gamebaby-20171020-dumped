#ifndef GMBB_Actor_HPP
#define GMBB_Actor_HPP


#include"gmbb_Figures.hpp"
#include"gmbb_Image.hpp"
#include"gmbb_Controller.hpp"
#include"covered_ptr"
#include<cstdio>
#include<string>


namespace gmbb{


class Director;
class Actor;


class
ExecutionContext
{
public:
  void  decode(std::string const&  s) noexcept{}

  void  step(Actor&  actor) noexcept{}

  bool  is_finished() const noexcept{return true;}

};


class
Actor
{
  static constexpr int  buffer_size = 8;


  std::string  name;

  Point  relative_point;

  bool  needing_to_redraw=true;

  covered_ptr<Director>  director;

  covered_ptr<Actor>  previous;
  covered_ptr<Actor>      next;

  std::string  action_buffer[buffer_size];

  int   writing_index=0;
  int   reading_index=0;

  int  number_of_actions=0;

  ExecutionContext  exectx;

public:
  Actor() noexcept{}

  void                set_name(char const*  name_)       noexcept{       name = name_;}
  std::string const&  get_name(                  ) const noexcept{return name        ;}

  virtual bool  is_director() const noexcept{return false;}

  void  enter_into_group(Director&  director_, Point  point) noexcept;
  void   exit_from_group(                                  ) noexcept;

  Director const*  get_director() const noexcept{return director.get_const_raw_pointer();}

  void  connect_to_previous(Actor&  target) noexcept;
  void  connect_to_next(    Actor&  target) noexcept;
  void  disconnect() noexcept;

  covered_ptr<Actor>  get_previous() const noexcept{return previous;}
  covered_ptr<Actor>  get_next()     const noexcept{return     next;}

  Actor const*  get_const_previous() const noexcept{return previous.get_const_raw_pointer();}
  Actor const*  get_const_next()     const noexcept{return     next.get_const_raw_pointer();}

  void  notify_needing_to_redraw() noexcept;

  void  cancel_needing_to_redraw() noexcept{needing_to_redraw = false;}

  bool  is_needing_to_redraw() const noexcept{return needing_to_redraw;}

  void  move_relative_point(int  x, int  y) noexcept;
  void  set_relative_point(Point  pt) noexcept{relative_point = pt;}

  Point  get_relative_point() const noexcept{return relative_point;}

  virtual void  render(Image&  dst, Point  dst_point) const noexcept{}

  virtual void  update() noexcept;

  virtual void  print() const noexcept{printf("%s(%p)",name.data(),this);}

};


}




#endif




