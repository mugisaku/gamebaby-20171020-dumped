#include"gmbb_Game_private.hpp"


namespace gmbb{


namespace{


constexpr int  square_size = 24;


class
BoardView: public Widget
{
public:
  game::Board const*  target;

  Point  point;

  BoardView(game::Board&  board) noexcept: target(&board){}

  void  render(Image&  dst) noexcept override;

} *view;



void
BoardView::
render(Image&  dst) noexcept
{
  constexpr int  w = screen_width /square_size;
  constexpr int  h = screen_height/square_size;

    for(int  y = 0;  y < h;  ++y)
    {
        for(int  x = 0;  x < w;  ++x)
        {
          Point  dst_point(point.x+(square_size*x),
                           point.y+(square_size*y));

          Point  src_point(dst_point.x/square_size,
                           dst_point.y/square_size);

            if((src_point.x >=                  0) &&
               (src_point.y >=                  0) &&
               (src_point.x <  game::board_width ) &&
               (src_point.y <  game::board_height))
            {
              auto&  sq = target->get_square_const(src_point.x,src_point.y);

              dst.draw_rectangle_safely(Rectangle(dst_point.x,dst_point.y,square_size,square_size),Pixel(white));
            }
        }
    }
}


}


void  move_board_view_to_up(){view->point.y -= 8;  update_board_view();}
void  move_board_view_to_left(){view->point.x -= 8;  update_board_view();}
void  move_board_view_to_right(){view->point.x += 8;  update_board_view();}
void  move_board_view_to_down(){view->point.y += 8;  update_board_view();}


void
show_board_view() noexcept
{
    if(!view)
    {
      view = new BoardView(board);
    }


  view->enter_into(root_widget,Point());
}


void
hide_board_view() noexcept
{
  view->leave_from_parent();
}


void
update_board_view() noexcept
{
  view->redraw();
}


}




