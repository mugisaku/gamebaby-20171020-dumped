#ifndef GMBB_Gadget_HPP
#define GMBB_Gadget_HPP


#include"gmbb_Figures.hpp"
#include"gmbb_Image.hpp"
#include"gmbb_Controller.hpp"
#include"covered_ptr"
#include<cstdio>
#include<string>


namespace gmbb{


class GadgetContainer;


class
Gadget
{
  std::string  name;

  Point  relative_point;

  bool  needing_to_redraw=true;

  covered_ptr<GadgetContainer>  container;

  covered_ptr<Gadget>  previous;
  covered_ptr<Gadget>      next;

public:
  void  set_name(char const*  name_) noexcept{name = name_;}

  void  enter_into_container(GadgetContainer&  container_, Point  point) noexcept;
  void   exit_from_container(                                          ) noexcept;

  GadgetContainer const*  get_container() const noexcept{return container.get_const_raw_pointer();}

  void  connect_to_previous(Gadget&  target) noexcept;
  void  connect_to_next(    Gadget&  target) noexcept;
  void  disconnect() noexcept;

  covered_ptr<Gadget>  get_previous() const noexcept{return previous;}
  covered_ptr<Gadget>  get_next()     const noexcept{return     next;}

  Gadget const*  get_const_previous() const noexcept{return previous.get_const_raw_pointer();}
  Gadget const*  get_const_next()     const noexcept{return     next.get_const_raw_pointer();}

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




