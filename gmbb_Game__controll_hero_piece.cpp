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


bool
is_hero_busy() noexcept
{
  return is_busy;
}




void
render_hero_piece(Piece const&  p, Image&  dst, Point  dst_point) noexcept
{
  constexpr int  u = square_size;

  int  x;
  int  y;

  int  w = u  ;
  int  h = u*2;

    switch(p.get_face_direction())
    {
  case(Direction::front):
      y = 0;
      break;
  case(Direction::front_left ):
      y = h*3;
      break;
  case(Direction::left       ):
      y = h*1;
      break;
  case(Direction::back_left  ):
      y = h*4;
      break;
  case(Direction::back       ):
      y = h*2;
      break;
  case(Direction::back_right ):
      y = h*4;
      w = -w;
      break;
  case(Direction::right      ):
      y = h*1;
      w = -w;
      break;
  case(Direction::front_right):
      y = h*3;
      w = -w;
    }


  static int const  table[] = {0,1,0,2};

  x = u*table[p.get_frame_count()%square_size/6];

  dst_point.y -= u;

  Rectangle  rect(x,y,w,h);

  p.revise_point(dst_point,rect);

  dst.transfer(*Piece::get_source_image(),rect,dst_point,p.get_relative_point().y+80);
}


}




