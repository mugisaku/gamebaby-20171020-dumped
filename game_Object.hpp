#ifndef game_Object_HPP
#define game_Object_HPP


#include"gmbb_Figures.hpp"
#include"gmbb_Image.hpp"
#include"game_Direction.hpp"
#include<covered_ptr>


namespace game{


enum class
ObjectFlag
{
  no_animation = 0x1,
  blink        = 0x2,
  invisible    = 0x4,

};


class
Object
{
  Direction  moving_direction=Direction::front;
  Direction    face_direction=Direction::front;

  gmbb::Point  rendering_point;

  int  action_index=0;
  int   frame_index=0;
  int   frame_count=0;

  covered_ptr<Object>  previous;
  covered_ptr<Object>      next;

public:
  virtual ~Object(){}

  void  set_rendering_point_by_current_square(int  square_size) noexcept;

  void  set_rendering_point(gmbb::Point  pt) noexcept{rendering_point = pt;}

  void  move_rendering_point(int  x, int  y) noexcept{rendering_point += gmbb::Point(x,y);}

  gmbb::Point  get_rendering_point() const noexcept{return rendering_point;}

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


  void  change_action_index(int  v) noexcept;
  int  get_action_index() const noexcept{return action_index;}

  covered_ptr<Object>  get_previous() const noexcept{return previous;}
  covered_ptr<Object>  get_next()     const noexcept{return     next;}

  Object const*  get_const_previous() const noexcept{return previous.get_const_raw_pointer();}
  Object const*  get_const_next()     const noexcept{return     next.get_const_raw_pointer();}

  void  link(covered_ptr<Object>  o) noexcept;
  void  unlink() noexcept;

  void  step() noexcept;

  virtual void  update() noexcept{}

  virtual void  render(gmbb::Image&  dst, gmbb::Point  point) const noexcept{}

  void  render_with_offset(gmbb::Image&  dst, gmbb::Point  offset) const noexcept{render(dst,rendering_point-offset);}

};


}




#endif




