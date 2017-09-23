#ifndef GMBB_CONTROLLER_HPP
#define GMBB_CONTROLLER_HPP


#include"gmbb_Figures.hpp"
#include<cstdint>
#include<cstdio>
#include<string>


namespace gmbb{


class
ButtonState
{
protected:
  uint32_t  flags=0;

public:
  struct Flag{
    int  data;

    constexpr Flag(int  v) noexcept: data(v){}
  };


  void  clear_state() noexcept{flags = 0;}

  void    set(Flag  flag)       noexcept{flags |=  flag.data;}
  void  unset(Flag  flag)       noexcept{flags &= ~flag.data;}
  bool   test(Flag  flag) const noexcept{return(flags&flag.data);}

};


class
Controller: public ButtonState
{
  uint32_t  time=0;

  Point  point;

public:
  void  change_point(int  x, int  y){point = Point(x,y);}

  Point  get_point() const noexcept{return point;}

  void  change_time(uint32_t  v) noexcept{time = v;}

  uint32_t  get_time() const noexcept{return time;}

};


constexpr ButtonState::Flag       up_button_pressed( 0x0001);
constexpr ButtonState::Flag       up_button_released(0x0002);
constexpr ButtonState::Flag     left_button_pressed( 0x0004);
constexpr ButtonState::Flag     left_button_released(0x0008);
constexpr ButtonState::Flag    right_button_pressed( 0x0010);
constexpr ButtonState::Flag    right_button_released(0x0020);
constexpr ButtonState::Flag     down_button_pressed( 0x0040);
constexpr ButtonState::Flag     down_button_released(0x0080);
constexpr ButtonState::Flag        p_button_pressed( 0x0100);
constexpr ButtonState::Flag        p_button_released(0x0200);
constexpr ButtonState::Flag        n_button_pressed( 0x0400);
constexpr ButtonState::Flag        n_button_released(0x0800);
constexpr ButtonState::Flag    start_button_pressed( 0x1000);
constexpr ButtonState::Flag    start_button_released(0x2000);
constexpr ButtonState::Flag    shift_button_pressed( 0x4000);
constexpr ButtonState::Flag    shift_button_released(0x8000);

constexpr ButtonState::Flag  mouse_lbutton_button_pressed( 0x10000);
constexpr ButtonState::Flag  mouse_lbutton_button_released(0x20000);
constexpr ButtonState::Flag  mouse_rbutton_button_pressed( 0x40000);
constexpr ButtonState::Flag  mouse_rbutton_button_released(0x80000);


}


#endif




