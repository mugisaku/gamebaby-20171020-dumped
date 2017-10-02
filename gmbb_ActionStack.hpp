#ifndef gmbb_ActionStack_HPP
#define gmbb_ActionStack_HPP




namespace gmbb{


class Gadget;


struct
Action
{
  template<typename  T> using Callback = void  (*)(T&  actor, int  count) noexcept;

  using PrimitiveCallback = void  (*)(Gadget&  actor, int  count) noexcept;

  PrimitiveCallback  callback;

  int  count;

  constexpr Action(PrimitiveCallback  cb=nullptr, int  c=0) noexcept:
  callback(cb),
  count(c){}

  template<typename  T>
  constexpr Action(Callback<T>  cb, int  c=0) noexcept:
  callback(reinterpret_cast<PrimitiveCallback>(cb)),
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
  template<typename  T>
  void  push(Action::Callback<T>  cb, int  count=1) noexcept
  {
    array[index++] = Action(cb,count);
  }


  void   pop() noexcept{--index;}

  operator bool() const noexcept{return index;}


  template<typename  T>
  void  operator()(T&  g) noexcept
  {
  START:

      if(index)
      {
        auto&  act = array[index-1];

          if(act.count)
          {
            reinterpret_cast<Action::Callback<T>>(act.callback)(g,--act.count);

              if(!act.count)
              {
                pop();
              }
          }

        else
          {
            pop();
          }
      }
  }

};


}




#endif




