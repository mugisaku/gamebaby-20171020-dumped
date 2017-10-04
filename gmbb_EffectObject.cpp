#include"gmbb_EffectObject.hpp"
#include"gmbb_ProtoBoard.hpp"




namespace gmbb{




void
EffectObject::
change_action_index(ActionIndex  i) noexcept
{
  action_index = i;

  reset_frame_count();
}


void
EffectObject::
update() noexcept
{
  ++frame_count;

    if(callback)
    {
      callback(*this);
    }


  x_position += x_vector;
  y_position += y_vector;
printf("%d\n",x_position.get_raw_value().data);
  set_relative_point(Point(*x_position,*y_position));
}


void
EffectObject::
render(Image&  dst, Point  dst_point) const noexcept
{
    for(int  i = 0;  i < number_of_rendering_orders;  ++i)
    {
      auto&  o = rendering_order_array[i];

      dst_point += o.dst_offset;

      revise_point(dst_point,o.src_rectangle);

      dst.transfer(*get_source_image(),o.src_rectangle,dst_point,get_relative_point().y+79);
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




