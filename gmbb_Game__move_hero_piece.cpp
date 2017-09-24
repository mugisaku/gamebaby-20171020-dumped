#include"gmbb_Game_private.hpp"


namespace gmbb{


void
move(game::Piece&  p, game::Square&  sq)
{
    if(!sq.get_piece() && (sq != game::SquareKind::wall))
    {
      p.get_square()->set_piece(nullptr);

      sq.set_piece(&p);
      p.set_square(&sq);

      update_board_view();
    }
}


void
move_hero_piece_to_forward()
{
  auto  sq = hero_piece->get_square();

  auto  dst = (*sq)[hero_piece->get_direction()];

    if(dst)
    {
      move(*hero_piece,*dst);
    }
}


void
turn_hero_piece_to_left()
{
  hero_piece->set_direction(get_left(hero_piece->get_direction()));

  update_board_view();
}


void
turn_hero_piece_to_right()
{
  hero_piece->set_direction(get_right(hero_piece->get_direction()));

  update_board_view();
}


void
move_hero_piece_to_backward()
{
  auto  sq = hero_piece->get_square();

  auto  dst = (*sq)[get_opposite(hero_piece->get_direction())];

    if(dst)
    {
      move(*hero_piece,*dst);
    }
}


}




