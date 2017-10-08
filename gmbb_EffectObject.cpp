#include"gmbb_EffectObject.hpp"
#include"gmbb_ProtoBoard.hpp"




namespace gmbb{




void
EffectObject::
change_action_index(ActionIndex  i) noexcept
{
  action_index = i;

  pattern_index = 0;

  reset_frame_count();
  reset_motion_count();
}


bool
EffectObject::
check_visible_count() noexcept
{
    if(invisible_count)
    {
      --invisible_count;

      return false;
    }


    if(!invisible_count)
    {
        if(visible_count)
        {
          --visible_count;

          return true;
        }


        if(!visible_count)
        {
            visible_count =   visible_interval;
          invisible_count = invisible_interval;
        }


      return true;
    }


  return false;
}


void
EffectObject::
update() noexcept
{
    if(!frozen_flag)
    {
      ++frame_count;
    }


  x_position += x_vector;
  y_position += y_vector;

  set_relative_point(Point(*(fixed_t("0.5")+x_position),
                           *(fixed_t("0.5")+y_position)));


    if(controll_callback)
    {
      controll_callback(*this);
    }
}


covered_ptr<Image>
EffectObject::
source_image;


void
EffectObject::
set_source_image(Image&  src) noexcept
{
  source_image = &src;
}


covered_ptr<Image>
EffectObject::
get_source_image() noexcept
{
  return source_image;
}


void
EffectObject::
revise_point(Point&  point, Rectangle const&   rect) noexcept
{
    if(point.x < -rect.w)
    {
        while(point.x < -rect.w)
        {
          point.x += board_image_width;
        }
    }

  else
    if(point.x >= board_image_width+rect.w)
    {
        while(point.x >= board_image_width+rect.w)
        {
          point.x -= board_image_width;
        }
    }


    if(point.y < -rect.h)
    {
        while(point.y < -rect.h)
        {
          point.y += board_image_height;
        }
    }

  else
    if(point.y >= board_image_height+rect.h)
    {
        while(point.y >= board_image_height+rect.h)
        {
          point.y -= board_image_height;
        }
    }
}


}




