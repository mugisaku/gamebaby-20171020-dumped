#include"gmbb_Game_private.hpp"


namespace gmbb{


namespace{


class
BoardView: public Actor
{
public:
  Point  point;

  BoardView() noexcept{}

  void  revise_point() noexcept;

  void  render(Image&  dst, Point  offset) const noexcept override;

} *view;



void
BoardView::
revise_point() noexcept
{
  point.transform(board_image_width,board_image_height);
}


namespace{
void
render_square(Square const&  sq, Image&  dst, Point  offset) noexcept
{
  Rectangle  rect(24*4,24*10,24,24);

    if(sq == SquareKind::room)
    {
      rect.y += 24;
    }


  dst.transfer(character_image,rect,offset,0);

  auto&  item = sq.get_item();

    if(item)
    {
      dst.transfer(character_image,get_rectangle_for_item(item),offset,0);
    }
}


void
render_row(Square const*  begin,
           Square const*  current,
           Square const*  end, Image&  dst, Point  offset) noexcept
{
    while(offset.x < screen_width)
    {
        if(current >= end)
        {
          current = begin;
        }


      render_square(*current++,dst,offset);

      offset.x += square_size;
    }
}
}


void
BoardView::
render(Image&  dst, Point  offset) const noexcept
{
  constexpr int  w = (screen_width /square_size);
  constexpr int  h = (screen_height/square_size);

  Point  start_point = point/square_size;
  Point    rem_point = point%square_size;

  int  dst_x = -rem_point.x;
  int  dst_y = -rem_point.y;

    while(dst_y < screen_height)
    {
        if(start_point.y >= board_height)
        {
          start_point.y = 0;
        }


      auto  line_begin = &board.get_square(0,start_point.y);
      auto       start = line_begin+start_point.x;
      auto    line_end = line_begin+board_width;

      render_row(line_begin,start,line_end,dst,Point(dst_x,dst_y));

      start_point.y +=           1;
              dst_y += square_size;
    }


  covered_ptr<Piece>  next = board.get_first();

    while(next)
    {
      next->cancel_needing_to_redraw();

        if(next->check_visible_count())
        {
          next->render(dst,-view->point);
        }


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


  view->enter_into_group(root_widget,Point());
}


void
hide_board_view() noexcept
{
  view->exit_from_group();
}


void
update_board_view() noexcept
{
  view->revise_point();

  view->notify_needing_to_redraw();
}




Rectangle
get_rectangle_for_item(SackItem const&  itm) noexcept
{
  int  x =     0;
  int  y = 24*10;

    switch(itm->get_kind())
    {
  case(GameItemKind::sword):
      break;
  case(GameItemKind::shield):
      y += 24;
      break;
  case(GameItemKind::belt):
      x += 24;
      break;
  case(GameItemKind::wand):
      x += 24;
      y += 24;
      break;
  case(GameItemKind::card):
      x += 24*2;
      break;
  case(GameItemKind::water):
      x += 24*2;
      y += 24;
      break;
    }


  return Rectangle(x,y,square_size,square_size);
}




}




