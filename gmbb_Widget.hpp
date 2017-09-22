#ifndef GMBB_Widget_HPP
#define GMBB_Widget_HPP


#include"gmbb_Figures.hpp"
#include"gmbb_Image.hpp"
#include"gmbb_Controller.hpp"
#include<list>


namespace gmbb{


namespace flags_of_widget{
constexpr int             hiding = 0x01;
constexpr int  needing_to_update = 0x02;
constexpr int  needing_to_redraw = 0x04;
}


using namespace flags_of_widget;


class
Widget
{
protected:
  Point  relative_point;

  uint32_t  flags=0;

  Rectangle  rectangle;

  Widget*  parent=nullptr;

  Widget*  first_child=nullptr;
  Widget*   last_child=nullptr;

  Widget*  previous_sibling=nullptr;
  Widget*      next_sibling=nullptr;

public:
          Widget() noexcept{}
          Widget(int  w, int  h) noexcept: rectangle(0,0,w,h){}
 virtual ~Widget(){clear();}

  void  clear() noexcept;

  void  enter_into(Widget&  parent, Point  point) noexcept;
  void  leave_from_parent(                      ) noexcept;

  Widget const*  get_parent() const noexcept{return parent;}

  void  notify_flag(int  flag) noexcept;

  void    set_flag(int  flag) noexcept{flags |=  flag;}
  void  unset_flag(int  flag) noexcept{flags &= ~flag;}
  bool   test_flag(int  flag) const noexcept{return flags&flag;}

  bool  is_needing_to_redraw() const noexcept{return(!test_flag(hiding) && test_flag(needing_to_redraw));}

  void  redraw() noexcept;
  void  show() noexcept;
  void  hide() noexcept;

  void  update() noexcept;

  virtual void  render(Image&  dst) noexcept;

  void  print() const noexcept;

};


}




#endif




