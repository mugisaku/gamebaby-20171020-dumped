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
notify_flag(int  flag) noexcept
{
    if(!test_flag(flag))
    {
      set_flag(flag);

        if(parent)
        {
          parent->notify_flag(flag);
        }
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

      child->notify_flag(needing_to_update);

      children.emplace_back(child);
    }
}




void
Widget::
show() noexcept
{
  unset_flag(hiding);

  notify_flag(needing_redraw);
}


void
Widget::
hide() noexcept
{
  set_flag(hiding);

  notify_flag(needing_redraw);
}




void
Widget::
update() noexcept
{
    if(test_flag(sleeping))
    {
      return;
    }


    if(test_flag(needing_to_update))
    {
      unset_flag(needing_to_update);
        set_flag(needing_to_redraw);

      rectangle.x = relative_point.x;
      rectangle.y = relative_point.y;

        if(parent)
        {
          rectangle.x += parent->rectangle.x;
          rectangle.y += parent->rectangle.y;
        }


        for(auto&  child: children)
        {
          child->update();
        }
    }
}

 
void
Widget::
controll(Controller const&  ctrl) noexcept
{
    if(!test_flag(sleeping))
    {
        for(auto&  child: children)
        {
          child->controll(ctrl);
        }
    }
}


void
Widget::
render(Image&  dst) noexcept
{
    if(is_needing_to_redraw())
    {
      unset_flag(needing_to_redraw);

        for(auto&  child: children)
        {
          child->render(dst);
        }
    }
}


}




