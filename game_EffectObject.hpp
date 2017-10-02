#ifndef game_EffectObject_HPP
#define game_EffectObject_HPP


#include"gmbb_Gadget.hpp"
#include"gmbb_ActionStack.hpp"
#include"game_Direction.hpp"


namespace game{


enum class
ObjectFlag
{
  no_animation = 0x1,
  blink        = 0x2,
  invisible    = 0x4,

};


class
EffectObject: public gmbb::Gadget
{
  Direction  moving_direction=Direction::front;
  Direction    face_direction=Direction::front;

  int  action_index=0;
  int   frame_index=0;
  int   frame_count=0;

  gmbb::Point  image_base_point;

  static covered_ptr<gmbb::Image>  source_image;

protected:
  gmbb::ActionStack  action_stack;

public:
  EffectObject(){}

  void  set_direction(       Direction  d)       noexcept{moving_direction = face_direction = d;}
  void  set_moving_direction(Direction  d) noexcept{moving_direction = d;}
  void  set_face_direction(  Direction  d) noexcept{  face_direction = d;}

  void  turn_face_direction_to_left(    ) noexcept{face_direction = get_right(   face_direction);}
  void  turn_face_direction_to_right(   ) noexcept{face_direction = get_left(    face_direction);}
  void  turn_face_direction_to_opposite() noexcept{face_direction = get_opposite(face_direction);}

  Direction  get_moving_direction() const noexcept{return moving_direction;}
  Direction  get_face_direction(  ) const noexcept{return   face_direction;}


  void  reset_frame() noexcept;

  void  increase_frame_index_when_over(int  limit) noexcept;

  int  get_frame_index() const noexcept{return frame_index;}
  int  get_frame_count() const noexcept{return frame_count;}

  void  push_action(gmbb::Action::Callback<EffectObject>  cb, int  count=1) noexcept{action_stack.push(cb,count);}

  bool  is_busy() const noexcept{return action_stack;}

  void  update() noexcept override;

  void  render(gmbb::Image&  dst, gmbb::Point  dst_point) const noexcept;


  static void  set_source_image(gmbb::Image&  src) noexcept;
  static covered_ptr<gmbb::Image>  get_source_image() noexcept;

};


}




#endif




