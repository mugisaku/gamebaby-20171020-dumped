#ifndef GMBB_CONTROLLER_HPP
#define GMBB_CONTROLLER_HPP


#include"gmbb_Figures.hpp"
#include<cstdint>
#include<cstdio>
#include<string>


namespace gmbb{


class
Controller
{
  uint32_t  state=0;
  uint32_t   time=0;

  Point  point;

public:
  struct Flag{
    int  data;

    constexpr Flag(int  v) noexcept: data(v){}
  };


  void  change_point(int  x, int  y){point = Point(x,y);}

  Point  get_point() const noexcept{return point;}

  void  change_time(uint32_t  v) noexcept{time = v;}

  uint32_t  get_time() const noexcept{return time;}

  void  clear_state() noexcept{state = 0;}

  void   set(Flag  flag)       noexcept{state |= flag.data;}
  bool  test(Flag  flag) const noexcept{return(state&flag.data);}

};


constexpr Controller::Flag       up_button_pressed( 0x0001);
constexpr Controller::Flag       up_button_released(0x0002);
constexpr Controller::Flag     left_button_pressed( 0x0004);
constexpr Controller::Flag     left_button_released(0x0008);
constexpr Controller::Flag    right_button_pressed( 0x0010);
constexpr Controller::Flag    right_button_released(0x0020);
constexpr Controller::Flag     down_button_pressed( 0x0040);
constexpr Controller::Flag     down_button_released(0x0080);
constexpr Controller::Flag        p_button_pressed( 0x0100);
constexpr Controller::Flag        p_button_released(0x0200);
constexpr Controller::Flag        n_button_pressed( 0x0400);
constexpr Controller::Flag        n_button_released(0x0800);
constexpr Controller::Flag    start_button_pressed( 0x1000);
constexpr Controller::Flag    start_button_released(0x2000);
constexpr Controller::Flag    shift_button_pressed( 0x4000);
constexpr Controller::Flag    shift_button_released(0x8000);

constexpr Controller::Flag  mouse_lbutton_button_pressed( 0x10000);
constexpr Controller::Flag  mouse_lbutton_button_released(0x20000);
constexpr Controller::Flag  mouse_rbutton_button_pressed( 0x40000);
constexpr Controller::Flag  mouse_rbutton_button_released(0x80000);


}


#endif




