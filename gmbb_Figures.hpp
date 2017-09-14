#ifndef GMBB_Figures_HPP
#define GMBB_Figures_HPP


#ifndef report
#define report printf("[report] %s, %s, %d\n",__FILE__,__func__,__LINE__);
#endif


namespace gmbb{


struct
Point
{
  int  x;
  int  y;

  constexpr Point(int  x=0, int  y=0) noexcept:
  x(x), y(y){}

};


struct
Rectangle: public Point
{
  int  w;
  int  h;

  constexpr Rectangle(int  x_=0, int  y_=0, int  w_=0, int  h_=0) noexcept:
  Point(x_,y_),
  w(w_),
  h(h_){}

};


struct
Triangle
{
  Point  a;
  Point  b;
  Point  c;

  constexpr Triangle(Point  a_=Point(), Point  b_=Point(), Point  c_=Point()) noexcept:
  a(a_), b(b_), c(c_){}

};


struct
Line
{
  Point  a;
  Point  b;

  constexpr Line(Point  a_=Point(), Point  b_=Point()) noexcept:
  a(a_), b(b_){}

};


}


#endif




