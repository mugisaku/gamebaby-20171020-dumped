#include"gmbb_Widget.hpp"
#include<cstdlib>




namespace gmbb{




void
Widget::
clear() noexcept
{
  children.clear();
}


void
Widget::
reposition() noexcept
{
  static_cast<Point&>(rectangle) = relative_point;

    if(parent)
    {
      rectangle.x += parent->rectangle.x;
      rectangle.y += parent->rectangle.y;
    }


    for(auto&  child: children)
    {
      child->reposition();
    }
}


void
Widget::
join(Widget*  child, Point  point) noexcept
{
    if(child)
    {
      child->parent = this;

      child->relative_point = point;

      children.emplace_back(child);
    }
}

 
void
Widget::
controll(Controller const&  ctrl) noexcept
{
    for(auto&  child: children)
    {
      child->controll(ctrl);
    }
}


void
Widget::
render(Image&  dst) noexcept
{
    for(auto&  child: children)
    {
      child->render(dst);
    }
}


}




