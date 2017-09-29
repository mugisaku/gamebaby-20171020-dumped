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


  actor.move_rendering_point(pt.x,pt.y);
  move_board_view(           pt.x,pt.y);
}
}


void
move(game::Piece&  p, game::Square&  sq)
{
    if(!sq.get_piece() && (sq != game::SquareKind::wall))
    {
      p.set_rendering_point_by_current_square(square_size);

p.get_rendering_point().print();
      p.get_square()->set_piece(nullptr);

      sq.set_piece(&p);
      p.set_square(&sq);

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




