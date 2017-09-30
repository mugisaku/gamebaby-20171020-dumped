#ifndef game_ActionStack_HPP
#define game_ActionStack_HPP




namespace game{


template<typename  T>
struct
Action
{
  using Callback = void  (*)(T&  actor, int  count) noexcept;

  Callback  callback;

  int  count;

  constexpr Action(Callback  cb=nullptr, int  c=0) noexcept:
  callback(cb),
  count(c){}

  class Stack
  {
  public:
    static constexpr int  capacity = 16;

  private:
    Action<T>  array[capacity];

    int  index=0;

  public:
    void  push(Action::Callback  cb, int  count=1) noexcept
    {
      array[index++] = Action(cb,count);
    }


    void   pop() noexcept{--index;}

    operator bool() const noexcept{return index;}

    void  operator()(T&  t) noexcept
    {
    START:

        if(index)
        {
          auto&  act = array[index-1];

            if(!act.count)
            {
              pop();

              goto START;
            }

          else
            {
              act.callback(t,--act.count);
            }
        }
    }

  };

};


}




#endif




