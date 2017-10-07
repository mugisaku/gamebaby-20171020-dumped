#ifndef gmbb_EffectObject_HPP
#define gmbb_EffectObject_HPP


#include"gmbb_Gadget.hpp"
#include"gmbb_Direction.hpp"
#include"gmbb_FixedPointNumber.hpp"
#include<cstdint>


namespace gmbb{


namespace bitop{
template<typename  T>  void    set_flag(T&  target, T  flag) noexcept{target |=  flag;}
template<typename  T>  void  unset_flag(T&  target, T  flag) noexcept{target &= ~flag;}
template<typename  T>  bool   test_flag(T const&  target, T  flag) noexcept{return target&flag;}
}


enum class  ActionIndex: int;


class
EffectObject: public Gadget
{
  Direction  moving_direction=Direction::front;
  Direction    face_direction=Direction::front;

  ActionIndex  action_index=static_cast<ActionIndex>(0);
  int  pattern_index=0;
  uint32_t  frame_count=0;

  FixedPointNumber  x_vector;
  FixedPointNumber  y_vector;

  FixedPointNumber  x_position;
  FixedPointNumber  y_position;

  bool  frozen_flag=false;

  int  visible_interval=1;
  int  visible_count=0;

  int  invisible_interval=0;
  int  invisible_count=0;

  uint32_t  i_state=0;
  uint32_t  x_state=0;

  static covered_ptr<Image>  source_image;

protected:
  template<typename  T>using   RenderCallback = void  (*)(T const&  self, Image&  dst, Point  dst_point);
  template<typename  T>using ControllCallback = void  (*)(T&  self);

  ControllCallback<EffectObject>  controll_callback=nullptr;
  RenderCallback<EffectObject>      render_callback=nullptr;

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

  uint32_t  get_i_state() const noexcept{return i_state;}
  uint32_t  get_x_state() const noexcept{return x_state;}

  void    set_x_flag(uint32_t  flag) noexcept{bitop::set_flag(  x_state,flag);}
  void  unset_x_flag(uint32_t  flag) noexcept{bitop::unset_flag(x_state,flag);}
  bool  test_x_flag(uint32_t  flag) const noexcept{return bitop::test_flag(x_state,flag);}

  void    set_i_flag(uint32_t  flag) noexcept{bitop::set_flag(  i_state,flag);}
  void  unset_i_flag(uint32_t  flag) noexcept{bitop::unset_flag(i_state,flag);}
  bool  test_i_flag(uint32_t  flag) const noexcept{return bitop::test_flag(i_state,flag);}

  ActionIndex  get_action_index() const noexcept{return action_index;}

  void  change_action_index(ActionIndex  i) noexcept;

  uint32_t     get_frame_count(             ) const noexcept{return frame_count    ;}
  void       reset_frame_count(uint32_t  v=0)       noexcept{       frame_count = v;}

  int   get_pattern_index(      ) const noexcept{return pattern_index    ;}
  void  set_pattern_index(int  i)       noexcept{       pattern_index = i;}


  void    freeze() noexcept{frozen_flag =  true;}
  void  unfreeze() noexcept{frozen_flag = false;}

  bool  is_frozen() const noexcept{return frozen_flag;}


  void  set_x_position(fixed_t  f) noexcept{x_position = f;}
  void  set_y_position(fixed_t  f) noexcept{y_position = f;}

  void  move_position(fixed_t  x, fixed_t  y) noexcept
  {
    x_position += x;
    y_position += y;
  }

  fixed_t  get_x_position() const noexcept{return x_position;}
  fixed_t  get_y_position() const noexcept{return y_position;}

  void  set_x_vector(fixed_t  f) noexcept{x_vector = f;}
  void  set_y_vector(fixed_t  f) noexcept{y_vector = f;}

  fixed_t  get_x_vector() const noexcept{return x_vector;}
  fixed_t  get_y_vector() const noexcept{return y_vector;}


  void    set_visible_interval(int  v) noexcept{  visible_interval = v;}
  void  set_invisible_interval(int  v) noexcept{invisible_interval = v;}


  void  set_controll_callback(ControllCallback<EffectObject>  cb) noexcept{controll_callback = cb;}
  void  set_render_callback(RenderCallback<EffectObject>  cb) noexcept{render_callback = cb;}

  bool  check_visible_count() noexcept;

  void  update() noexcept override;

  void  render(Image&  dst, Point  dst_point) const noexcept override
  {
      if(render_callback)
      {
        render_callback(*this,dst,dst_point);
      }
  }

  static void  revise_point(Point&  point, Rectangle const&   rect) noexcept;

  static void  set_source_image(Image&  src) noexcept;
  static covered_ptr<Image>  get_source_image() noexcept;

};


}




#endif




