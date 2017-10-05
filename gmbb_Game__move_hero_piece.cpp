#include"gmbb_Game_private.hpp"


namespace gmbb{




enum class
ActionIndex: int
{
  null,
  moving,
  message,
};




namespace{


bool
is_busy;


void
set_order_of_when_moving(Piece&  p) noexcept
{
  constexpr int  u = square_size  ;
  constexpr int  h = square_size*2;

  static RenderingOrder  const front[3] = 
  {
    RenderingOrder(u*0,h*0,u,h,Point(0,-u)),
    RenderingOrder(u*1,h*0,u,h,Point(0,-u)),
    RenderingOrder(u*2,h*0,u,h,Point(0,-u)),
  };


  static RenderingOrder  const front_left[3] = 
  {
    RenderingOrder(u*0,h*3,u,h,Point(0,-u)),
    RenderingOrder(u*1,h*3,u,h,Point(0,-u)),
    RenderingOrder(u*2,h*3,u,h,Point(0,-u)),
  };


  static RenderingOrder  const left[3] = 
  {
    RenderingOrder(u*0,h*1,u,h,Point(0,-u)),
    RenderingOrder(u*1,h*1,u,h,Point(0,-u)),
    RenderingOrder(u*2,h*1,u,h,Point(0,-u)),
  };


  static RenderingOrder  const back_left[3] = 
  {
    RenderingOrder(u*0,h*4,u,h,Point(0,-u)),
    RenderingOrder(u*1,h*4,u,h,Point(0,-u)),
    RenderingOrder(u*2,h*4,u,h,Point(0,-u)),
  };


  static RenderingOrder  const back[3] = 
  {
    RenderingOrder(u*0,h*2,u,h,Point(0,-u)),
    RenderingOrder(u*1,h*2,u,h,Point(0,-u)),
    RenderingOrder(u*2,h*2,u,h,Point(0,-u)),
  };


  static RenderingOrder  const back_right[3] = 
  {
    RenderingOrder(u*0,h*4,-u,h,Point(0,-u)),
    RenderingOrder(u*1,h*4,-u,h,Point(0,-u)),
    RenderingOrder(u*2,h*4,-u,h,Point(0,-u)),
  };


  static RenderingOrder  const right[3] = 
  {
    RenderingOrder(u*0,h*1,-u,h,Point(0,-u)),
    RenderingOrder(u*1,h*1,-u,h,Point(0,-u)),
    RenderingOrder(u*2,h*1,-u,h,Point(0,-u)),
  };


  static RenderingOrder  const front_right[3] = 
  {
    RenderingOrder(u*0,h*3,-u,h,Point(0,-u)),
    RenderingOrder(u*1,h*3,-u,h,Point(0,-u)),
    RenderingOrder(u*2,h*3,-u,h,Point(0,-u)),
  };


  RenderingOrder const*  ptr;

    switch(p.get_face_direction())
    {
  case(Direction::front      ): ptr = front;break;
  case(Direction::front_left ): ptr = front_left;break;
  case(Direction::left       ): ptr = left;break;
  case(Direction::back_left  ): ptr = back_left;break;
  case(Direction::back       ): ptr = back;break;
  case(Direction::back_right ): ptr = back_right;break;
  case(Direction::right      ): ptr = right;break;
  case(Direction::front_right): ptr = front_right;break;
    }


  static int const  table[] = {0,1,0,2};

  auto  i = table[p.get_frame_count()%square_size/6];

  return p.set_rendering_order(ptr+i);
}


void
pickup_item_if_is(Piece&  actor) noexcept
{
  auto&  sq = *actor.get_square();

  auto&  i = sq.get_item();

    if(i)
    {
      actor.change_action_index(ActionIndex::message);

      char16_t  buf[256]=u"";

      auto  pickedup = hero.get_sack().try_to_push_item(i);

      char const*  fmt = "%sを　ひろった";

      auto  name = i->get_name();

        if(!pickedup)
        {
          fmt = "%sがおちていたが　もちものがいっぱいで　ひろえない";
        }

      else
        {
          i = SackItem();
        }


      u16snprintf(buf,sizeof(buf),fmt,name);

      start_message(buf);
    }

  else
    {
      actor.change_action_index(ActionIndex::null);

      is_busy = false;
    }
}


bool
prepare_to_move(Piece&  p, Square&  sq)
{
    if(!sq.get_piece() && (sq != SquareKind::wall))
    {
      p.get_square()->set_piece(nullptr);

      sq.set_piece(&p);
      p.set_square(&sq);

      Point  pt;

        switch(p.get_moving_direction())
        {
      case(Direction::front      ): pt = Point( 0, 1);break;
      case(Direction::front_left ): pt = Point(-1, 1);break;
      case(Direction::left       ): pt = Point(-1, 0);break;
      case(Direction::back_left  ): pt = Point(-1,-1);break;
      case(Direction::back       ): pt = Point( 0,-1);break;
      case(Direction::back_right ): pt = Point( 1,-1);break;
      case(Direction::right      ): pt = Point( 1, 0);break;
      case(Direction::front_right): pt = Point( 1, 1);break;
        }


      p.change_action_index(ActionIndex::moving);

      p.set_x_vector(fixed_t(pt.x));
      p.set_y_vector(fixed_t(pt.y));

      is_busy = true;
    }
}


}


void
controll_hero_piece(Piece&  self) noexcept
{
  set_order_of_when_moving(self);

    switch(self.get_action_index())
    {
  case(ActionIndex::null):
      break;
  case(ActionIndex::moving):
    {
      move_board_view(*self.get_x_vector(),
                      *self.get_y_vector());

        if(self.get_frame_count() > square_size)
        {
          self.set_x_vector(fixed_t());
          self.set_y_vector(fixed_t());

          pickup_item_if_is(self);
        }
    }
      break;
  case(ActionIndex::message):
    {
      close_message_window();

      self.change_action_index(ActionIndex::null);

      is_busy = false;
    }
      break;
    }


  update_board_view();
}


void
move_hero_piece_to_forward()
{
  auto  sq = hero_piece->get_square();

  auto  d = hero_piece->get_face_direction();

  hero_piece->set_moving_direction(d);


  auto  dst = (*sq)[d];

    if(dst)
    {
      prepare_to_move(*hero_piece,*dst);
    }
}


void
turn_hero_piece_to_left()
{
  hero_piece->turn_face_direction_to_left();

  set_order_of_when_moving(*hero_piece);

  update_board_view();
}


void
turn_hero_piece_to_right()
{
  hero_piece->turn_face_direction_to_right();

  set_order_of_when_moving(*hero_piece);

  update_board_view();
}


void
move_hero_piece_to_backward()
{
  auto  sq = hero_piece->get_square();

  auto  d = get_opposite(hero_piece->get_face_direction());

  hero_piece->set_moving_direction(d);


  auto  dst = (*sq)[d];

    if(dst)
    {
      prepare_to_move(*hero_piece,*dst);
    }
}


bool
is_hero_busy() noexcept
{
  return is_busy;
}


}




