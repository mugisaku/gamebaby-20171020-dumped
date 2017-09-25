#include"gmbb_Game_private.hpp"


namespace gmbb{


void
move(game::Piece&  p, game::Direction  d, game::Square&  sq)
{
    if(!sq.get_piece() && (sq != game::SquareKind::wall))
    {
      p.get_square()->set_piece(nullptr);

      sq.set_piece(&p);
      p.set_square(&sq);
//printf("%3d %3d\n",sq.get_x(),sq.get_y());
      update_board_view();

      using game::Direction;

        switch(d)
        {
      case(Direction::front):
          move_board_view_to_down();
          break;
      case(Direction::front_left):
          move_board_view_to_left();
          move_board_view_to_down();
          break;
      case(Direction::left):
          move_board_view_to_left();
          break;
      case(Direction::back_left):
          move_board_view_to_up();
          move_board_view_to_left();
          break;
      case(Direction::back):
          move_board_view_to_up();
          break;
      case(Direction::back_right):
          move_board_view_to_up();
          move_board_view_to_right();
          break;
      case(Direction::right):
          move_board_view_to_right();
          break;
      case(Direction::front_right):
          move_board_view_to_down();
          move_board_view_to_right();
          break;
        }
    }
}


void
move_hero_piece_to_forward()
{
  auto  sq = hero_piece->get_square();

  auto  d = hero_piece->get_direction();

  auto  dst = (*sq)[d];

    if(dst)
    {
      move(*hero_piece,d,*dst);
    }
}


void
turn_hero_piece_to_left()
{
  hero_piece->set_direction(get_right(hero_piece->get_direction()));

  update_board_view();
}


void
turn_hero_piece_to_right()
{
  hero_piece->set_direction(get_left(hero_piece->get_direction()));

  update_board_view();
}


void
move_hero_piece_to_backward()
{
  auto  sq = hero_piece->get_square();

  auto  d = get_opposite(hero_piece->get_direction());

  auto  dst = (*sq)[d];

    if(dst)
    {
      move(*hero_piece,d,*dst);
    }
}


}




