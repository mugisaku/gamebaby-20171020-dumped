#ifndef GMBB_Widget_HPP
#define GMBB_Widget_HPP


#include"gmbb_Figures.hpp"
#include"gmbb_Image.hpp"
#include"gmbb_Controller.hpp"
#include<list>


namespace gmbb{


namespace flags_of_widget{
constexpr int             hiding = 0x02;
constexpr int  needing_to_update = 0x04;
constexpr int  needing_to_redraw = 0x08;
}


using namespace flags_of_widget;


class
Widget
{
protected:
  Point  relative_point;

  uint32_t  flags=0;

  Rectangle  rectangle;

  std::list<Widget*>  children;

  Widget*  parent=nullptr;

public:
          Widget() noexcept{}
          Widget(int  w, int  h) noexcept: rectangle(0,0,w,h){}
 virtual ~Widget(){clear();}

  void  clear() noexcept;

  void  join(Widget*  child, Point  point) noexcept;

  void  notify_flag(int  flag) noexcept;

  void    set_flag(int  flag) noexcept{flags |=  flag;}
  void  unset_flag(int  flag) noexcept{flags &= ~flag;}
  bool   test_flag(int  flag) const noexcept{return flags&flag;}

  bool  is_needing_to_redraw() const noexcept{return(!test_flag(hiding) && test_flag(needing_to_redraw));}

  void  show() noexcept;
  void  hide() noexcept;

  void  update() noexcept;

  virtual void  render(Image&  dst) noexcept;

};


}




#endif




