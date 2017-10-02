#include"gmbb_Game_private.hpp"


namespace gmbb{


namespace{
void
move_(game::Piece&  actor, int  count) noexcept
{
  using game::Direction;

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
pickup(game::Piece&  actor, int  count) noexcept
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
          i = game::SackItem();
        }


      u16snprintf(buf,sizeof(buf),fmt,name);

      start_message(buf);
    }
}
}


void
move(game::Piece&  p, game::Square&  sq)
{
    if(!sq.get_piece() && (sq != game::SquareKind::wall))
    {
      p.set_rendering_point_by_current_square();

      p.get_square()->set_piece(nullptr);

      sq.set_piece(&p);
      p.set_square(&sq);

      p.push_action(pickup,2);
      p.push_action(move_,square_size);
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
      move(*hero_piece,*dst);
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
      move(*hero_piece,*dst);
    }
}


}




