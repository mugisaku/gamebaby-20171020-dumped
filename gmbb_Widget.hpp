#ifndef GMBB_Widget_HPP
#define GMBB_Widget_HPP


#include"gmbb_Figures.hpp"
#include"gmbb_Image.hpp"
#include"gmbb_Controller.hpp"
#include<list>
#include<memory>


namespace gmbb{


class
Widget
{
protected:
  Point  relative_point;

  Rectangle  rectangle;

  std::list<std::unique_ptr<Widget>>  children;

  Widget*  parent=nullptr;

public:
          Widget() noexcept{}
          Widget(int  w, int  h) noexcept: rectangle(0,0,w,h){}
 virtual ~Widget(){clear();}

  void  clear() noexcept;

  void  join(Widget*  child, Point  point) noexcept;

  void  reposition() noexcept;

  virtual void  controll(Controller const&  ctrl) noexcept;

  virtual void  render(Image&  dst) noexcept;

};


}




#endif




