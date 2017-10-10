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


struct
Address
{
  uint8_t  a=0;
  uint8_t  b=0;
  uint8_t  c=0;
  uint8_t  d=0;

  constexpr Address(uint8_t  a_=0, uint8_t  b_=0, uint8_t  c_=0, uint8_t  d_=0):
  a(a_), b(b_), c (c_), d(d_){}

};


class
Actor
{
  std::string  name;

  Point  relative_point;

  bool  needing_to_redraw=true;

  covered_ptr<Director>  director;

  covered_ptr<Actor>  previous;
  covered_ptr<Actor>      next;

public:
  void  set_name(char const*  name_) noexcept{name = name_;}

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

  virtual void  update() noexcept{}

  virtual void  print() const noexcept{printf("%s(%p)",name.data(),this);}

};


}




#endif




