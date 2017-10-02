#include"gmbb_Game_private.hpp"


namespace gmbb{


namespace{


using  game::Piece;
using game::Square;


constexpr int  square_size = 24;

constexpr int  board_image_w = (square_size*game::board_width );
constexpr int  board_image_h = (square_size*game::board_height);


class
BoardView: public Gadget
{
public:
  Point  point;

  BoardView() noexcept{}

  void  revise_point() noexcept;

  void  render(Image&  dst, Point  dst_point) const noexcept override;

} *view;



void
BoardView::
revise_point() noexcept
{
    if(point.x < 0)
    {
        while(point.x < 0)
        {
          point.x += board_image_w;
        }
    }

  else
    if(point.x >= board_image_w)
    {
        while(point.x >= board_image_w)
        {
          point.x -= board_image_w;
        }
    }


    if(point.y < 0)
    {
        while(point.y < 0)
        {
          point.y += board_image_h;
        }
    }

  else
    if(point.y >= board_image_h)
    {
        while(point.y >= board_image_h)
        {
          point.y -= board_image_h;
        }
    }
}


namespace{
void
render_square(game::Square const&  sq, Image&  dst, Point  dst_point) noexcept
{
  Rectangle  rect(24*4,24*10,24,24);

    if(sq == game::SquareKind::room)
    {
      rect.y += 24;
    }


  dst.transfer(character_image,rect,dst_point,0);

  auto&  item = sq.get_item();

    if(item)
    {
      int  x =     0;
      int  y = 24*10;

        switch(item->get_kind())
        {
      case(game::GameItemKind::sword):
          break;
      case(game::GameItemKind::shield):
          y += 24;
          break;
      case(game::GameItemKind::belt):
          x += 24;
          break;
      case(game::GameItemKind::wand):
          x += 24;
          y += 24;
          break;
      case(game::GameItemKind::card):
          x += 24*2;
          break;
      case(game::GameItemKind::water):
          x += 24*2;
          y += 24;
          break;
        }


      dst.transfer(character_image,Rectangle(x,y,24,24),dst_point,0);
    }
}


void
render_row(Square const*  begin,
           Square const*  current,
           Square const*  end, Image&  dst, Point  dst_point) noexcept
{
    while(dst_point.x < screen_width)
    {
        if(current >= end)
        {
          current = begin;
        }


      render_square(*current++,dst,dst_point);

      dst_point.x += square_size;
    }
}
}


void
BoardView::
render(Image&  dst, Point  dst_point) const noexcept
{
/*
static int  n;

printf("%4d\n",n++);
fflush(stdout);
*/
  constexpr int  w = (screen_width /square_size);
  constexpr int  h = (screen_height/square_size);

  Point  start_point = point/square_size;
  Point    rem_point = point%square_size;

  int  dst_x = -rem_point.x;
  int  dst_y = -rem_point.y;

    while(dst_y < screen_height)
    {
        if(start_point.y >= game::board_height)
        {
          start_point.y = 0;
        }


      auto  line_begin = &board.get_square(0,start_point.y);
      auto       start = line_begin+start_point.x;
      auto    line_end = line_begin+game::board_width;

      render_row(line_begin,start,line_end,dst,Point(dst_x,dst_y));

      start_point.y +=           1;
              dst_y += square_size;
    }


  covered_ptr<Piece>  next = board.get_first();

    while(next)
    {
      next->cancel_needing_to_redraw();

      next->render(dst,next->get_relative_point()-view->point);

      next = next->get_next();
    }
}


}


Point
get_board_view_offset() noexcept
{
  return view->point;
}


void
move_board_view(int  x, int  y) noexcept
{
  view->point.x += x;
  view->point.y += y;

  update_board_view();
}


void
show_board_view() noexcept
{
    if(!view)
    {
      view = new BoardView;

      auto&  sq = *hero_piece->get_square();

      view->point.x = (24*sq.get_x())-(screen_width /2);
      view->point.y = (24*sq.get_y())-(screen_height/2);

      view->set_name("board view");
    }


  view->enter_into_container(root_widget,Point());
}


void
hide_board_view() noexcept
{
  view->exit_from_container();
}


void
update_board_view() noexcept
{
  view->revise_point();

  view->notify_needing_to_redraw();
}


}




