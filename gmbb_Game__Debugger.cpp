#include"gmbb_Game_private.hpp"


namespace gmbb{


namespace{


class
Debugger: public Actor
{
public:
  void  render(Image&  dst, Point  offset) const noexcept;

} *dbg;


void
Debugger::
render(gmbb::Image&  dst, Point  offset) const noexcept
{
  char  buf[256];

  offset += get_relative_point();

  auto  hpt = hero_piece->get_relative_point();
  auto  hsq = hero_piece->get_square();
  auto  vpt = get_board_view_offset();

  snprintf(buf,sizeof(buf),"HERO point %3d %3d",hpt.x,hpt.y);

  dst.print(buf,offset,glset);

  offset.y += 14;

  snprintf(buf,sizeof(buf),"HERO square %3d %3d",hsq->get_x(),hsq->get_y());

  dst.print(buf,offset,glset);

  offset.y += 14;

  snprintf(buf,sizeof(buf),"view offset %3d %3d",vpt.x,vpt.y);

  dst.print(buf,offset,glset);

  offset.y += 14;

  snprintf(buf,sizeof(buf),"pieces %3d",board.get_number_of_actors());

  dst.print(buf,offset,glset);

  offset.y += 14;
}


}


void
show_debugger() noexcept
{
    if(!dbg)
    {
      dbg = new Debugger;

      dbg->set_name("debugger");
    }


  dbg->enter_into_group(root_widget,Point(0,160));
}


void
hide_debugger() noexcept
{
  dbg->exit_from_group();
}


void
update_debugger() noexcept
{
  dbg->notify_needing_to_redraw();
}



}




