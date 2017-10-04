#include"gmbb_Game_private.hpp"


namespace gmbb{




enum class
ActionIndex: int
{
  null,
  moving,
};




namespace{


void
set_order_of_when_moving(Piece&  p) noexcept
{
  constexpr int  u = square_size  ;
  constexpr int  h = square_size*2;

  static RenderingOrder  const front[3] = 
  {
    RenderingOrder(u*0,u*0,u,h,Point(0,-u)),
    RenderingOrder(u*1,u*0,u,h,Point(0,-u)),
    RenderingOrder(u*2,u*0,u,h,Point(0,-u)),
  };


  RenderingOrder const*  ptr;

    switch(p.get_face_direction())
    {
  case(Direction::front      ): ptr = front;break;
  case(Direction::front_left ): ptr = front;break;
  case(Direction::left       ): ptr = front;break;
  case(Direction::back_left  ): ptr = front;break;
  case(Direction::back       ): ptr = front;break;
  case(Direction::back_right ): ptr = front;break;
  case(Direction::right      ): ptr = front;break;
  case(Direction::front_right): ptr = front;break;
    }


  auto  i = p.get_frame_count()&1;

  return p.set_rendering_order(ptr+i);
}


void
move_(Piece&  actor, int  count) noexcept
{
  Point  pt;

    switch(actor.get_moving_direction())
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


  actor.move_relative_point(pt.x,pt.y);
  move_board_view(          pt.x,pt.y);
}
void
pickup_item_if_is(Piece&  actor, int  count) noexcept
{
    if(!count)
    {
      close_message_window();

      return;
    }


  auto&  sq = *actor.get_square();

  auto&  i = sq.get_item();

    if(i)
    {
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
}


bool
prepare_to_move(Piece&  p, Square&  sq)
{
    if(!sq.get_piece() && (sq != SquareKind::wall))
    {
      p.get_square()->set_piece(nullptr);

      sq.set_piece(&p);
      p.set_square(&sq);

      p.change_action_index(ActionIndex::moving);
    }
}


}


void
controll_hero_piece(Piece&  self) noexcept
{
    switch(self.get_action_index())
    {
  case(ActionIndex::null):
    {
      static RenderingOrder const  orders[] = {
        RenderingOrder(0,0,24,48,Point(0,0)),
      };


      hero_piece->set_rendering_order(orders);
    }
      break;
  case(ActionIndex::moving):
    {
      set_order_of_when_moving(self);

      self.set_x_vector(fixed_t(1));
    }
      break;
    }

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

  update_board_view();
}


void
turn_hero_piece_to_right()
{
  hero_piece->turn_face_direction_to_right();

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


}




