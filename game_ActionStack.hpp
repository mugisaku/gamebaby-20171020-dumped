#ifndef game_ActionStack_HPP
#define game_ActionStack_HPP




namespace game{


class Piece;


struct
Action
{
  using Callback = void  (*)(Piece&  actor, int  count) noexcept;

  Callback  callback;

  int  count;

  constexpr Action(Callback  cb=nullptr, int  c=0) noexcept:
  callback(cb),
  count(c){}

};


class
ActionStack
{
public:
  static constexpr int  capacity = 16;

private:
  Action  array[capacity];

  int  index=0;

public:
  void  push(Action::Callback  cb, int  count=1) noexcept;
  void   pop(                                  ) noexcept;

  operator bool() const noexcept{return index;}

  void  operator()(Piece&  p) noexcept;

};


}




#endif




