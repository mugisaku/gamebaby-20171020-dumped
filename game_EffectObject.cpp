#include"game_EffectObject.hpp"


namespace game{




void
EffectObject::
reset_frame() noexcept
{
  frame_count = 0;
  frame_index = 0;
}


void
EffectObject::
increase_frame_index_when_over(int  limit) noexcept
{
    if(frame_count >= limit)
    {
      frame_count  = 0;
      frame_index += 1;
    }
}




void
EffectObject::
update() noexcept
{
  Gadget::update();

  ++frame_count;

  increase_frame_index_when_over(8);

    if(get_frame_index() >= 4)
    {
      reset_frame();
    }


  action_stack(*this);
}


void
EffectObject::
render(gmbb::Image&  dst, gmbb::Point  dst_point) const noexcept
{
  dst.transfer(*get_source_image(),gmbb::Rectangle(0,0,24,24),dst_point,get_relative_point().y);
}




covered_ptr<gmbb::Image>
EffectObject::
source_image;


void
EffectObject::
set_source_image(gmbb::Image&  src) noexcept
{
  source_image = &src;
}


covered_ptr<gmbb::Image>
EffectObject::
get_source_image() noexcept
{
  return source_image;
}


}




