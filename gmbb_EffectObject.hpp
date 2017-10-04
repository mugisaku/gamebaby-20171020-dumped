#ifndef gmbb_EffectObject_HPP
#define gmbb_EffectObject_HPP


#include"gmbb_Gadget.hpp"
#include"gmbb_Direction.hpp"
#include"gmbb_FixedPointNumber.hpp"
#include<cstdint>


namespace gmbb{


enum class
ObjectFlag
{
  no_animation = 0x1,
  blink        = 0x2,
  invisible    = 0x4,

};


struct
RenderingOrder
{
  Rectangle  src_rectangle;

  Point  dst_offset;

  constexpr RenderingOrder(int  x, int  y, int  w, int  h, Point  dst):
  src_rectangle(x,y,w,h),
  dst_offset(dst){}

};


namespace bitop{
template<typename  T>  void    set_flag(T&  target, T  flag) noexcept{target |=  flag;}
template<typename  T>  void  unset_flag(T&  target, T  flag) noexcept{target &= ~flag;}
template<typename  T>  bool   test_flag(T const&  target, T  flag) noexcept{return target&flag;}
}


enum class  ActionIndex: int;


class
EffectObject: public Gadget
{
  template<typename  T>using Callback = void  (*)(T&  self) noexcept;

  Callback<EffectObject>  callback=nullptr;

  Direction  moving_direction=Direction::front;
  Direction    face_direction=Direction::front;

  RenderingOrder const*  rendering_order_array=nullptr;

  int  number_of_rendering_orders=0;

  ActionIndex  action_index=static_cast<ActionIndex>(0);
  int  frame_count=0;

  FixedPointNumber  x_vector;
  FixedPointNumber  y_vector;

  FixedPointNumber  x_position;
  FixedPointNumber  y_position;

  uint32_t  i_state=0;
  uint32_t  x_state=0;

  static covered_ptr<Image>  source_image;

  template<typename  T>
  Callback<EffectObject>
  convert(Callback<T>  cb) noexcept
  {
    return reinterpret_cast<Callback<EffectObject>>(cb);
  }

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
  bool  test_x_flag(uint32_t  flag) const noexcept{bitop::test_flag(x_state,flag);}

  void    set_i_flag(uint32_t  flag) noexcept{bitop::set_flag(  i_state,flag);}
  void  unset_i_flag(uint32_t  flag) noexcept{bitop::unset_flag(i_state,flag);}
  bool  test_i_flag(uint32_t  flag) const noexcept{bitop::test_flag(i_state,flag);}

  ActionIndex  get_action_index() const noexcept{return action_index;}

  void  change_action_index(ActionIndex  i) noexcept;

  int     get_frame_count(        ) const noexcept{return frame_count    ;}
  void  reset_frame_count(int  v=0)       noexcept{       frame_count = v;}


  void  set_rendering_order(RenderingOrder const*  orders, int  n=1) noexcept
  {
    rendering_order_array = orders;
    number_of_rendering_orders = n;
  }


  void  set_x_position(fixed_t  f) noexcept{x_position = f;}
  void  set_y_position(fixed_t  f) noexcept{y_position = f;}

  fixed_t  get_x_position() const noexcept{return x_position;}
  fixed_t  get_y_position() const noexcept{return y_position;}

  void  set_x_vector(fixed_t  f) noexcept{x_vector = f;}
  void  set_y_vector(fixed_t  f) noexcept{y_vector = f;}

  fixed_t  get_x_vector() const noexcept{return x_vector;}
  fixed_t  get_y_vector() const noexcept{return y_vector;}


  void  set_callback(Callback<EffectObject>  cb) noexcept{callback = cb;}

  template<typename  T> void  set_callback(Callback<T>  cb) noexcept{callback = convert(cb);}

  void  update() noexcept override;

  void  render(Image&  dst, Point  dst_point) const noexcept;


  static void  revise_point(Point&  point, Rectangle const&   rect) noexcept;

  static void  set_source_image(Image&  src) noexcept;
  static covered_ptr<Image>  get_source_image() noexcept;

};


}




#endif




