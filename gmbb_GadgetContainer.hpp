#ifndef GMBB_GadgetContainer_HPP
#define GMBB_GadgetContainer_HPP


#include"gmbb_Gadget.hpp"


namespace gmbb{


class
GadgetContainer: public Gadget
{
  covered_ptr<Gadget>  first;
  covered_ptr<Gadget>   last;

public:
  void  insert_to_first(Gadget&  target) noexcept;
  void  insert_to_last( Gadget&  target) noexcept;

  void  remove(Gadget&  target) noexcept;

  covered_ptr<Gadget>  get_first() const noexcept{return first;}
  covered_ptr<Gadget>  get_last()  const noexcept{return  last;}

  Gadget const*  get_const_first() const noexcept{return first.get_const_raw_pointer();}
  Gadget const*  get_const_last()  const noexcept{return  last.get_const_raw_pointer();}

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

  void  print() const noexcept override;

};


}




#endif




