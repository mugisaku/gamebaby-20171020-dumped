#include"gmbb_Widget.hpp"
#include<cstdlib>




namespace gmbb{




void
Widget::
clear() noexcept
{
    while(last_child)
    {
      auto  child = last_child                          ;
                    last_child = child->previous_sibling;

      child->previous_sibling = nullptr;
      child->next_sibling     = nullptr;
      child->parent           = nullptr;
    }


  first_child = nullptr;
   last_child = nullptr;

  notify_flag(needing_to_redraw);
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
enter_into(Widget&  parent, Point  point) noexcept
{
    if(!this->parent)
    {
      this->parent = &parent;

      this->relative_point = point;

      notify_flag(needing_to_update);

      this->previous_sibling = parent.last_child       ;
                               parent.last_child = this;

        if(!parent.first_child)
        {
          parent.first_child = this;
        }


        if(this->previous_sibling)
        {
          this->previous_sibling->next_sibling = this;
        }
    }
}


void
Widget::
leave_from_parent() noexcept
{
    if(this->parent)
    {
      auto  prev = this->previous_sibling          ;
                   this->previous_sibling = nullptr;

      auto  next = this->next_sibling          ;
                   this->next_sibling = nullptr;

        if(prev){prev->next_sibling     = next;}
        if(next){next->previous_sibling = prev;}


        if(this->parent->first_child == this)
        {
          this->parent->first_child = next;
        }


        if(this->parent->last_child == this)
        {
          this->parent->last_child = prev;
        }


      this->parent = nullptr;
    }
}




void
Widget::
show() noexcept
{
  unset_flag(hiding);

  notify_flag(needing_to_redraw);
}


void
Widget::
hide() noexcept
{
  set_flag(hiding);

  notify_flag(needing_to_redraw);
}




void
Widget::
update() noexcept
{
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


      auto  child = first_child;

        while(child)
        {
          child->update();

          child = child->next_sibling;
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

      auto  child = first_child;

        while(child)
        {
          child->render(dst);

          child = child->next_sibling;
        }
    }
}


}




