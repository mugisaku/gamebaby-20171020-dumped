#include"gmbb_Game_private.hpp"


namespace gmbb{


namespace{


class
StatusMonitor: public Gadget
{
public:
  void  render(Image&  dst, Point  dst_point) const noexcept;

} *mon;


void
StatusMonitor::
render(gmbb::Image&  dst, Point  dst_point) const noexcept
{
  char  buf[256];

  auto  hero_p = board.get_hero_piece();

  snprintf(buf,sizeof(buf),"HP%3d/%3d",hero_p->get_hp(),hero_p->get_hp_max());

  dst.print(buf,dst_point,glset);
}


}


void
show_status_monitor() noexcept
{
    if(!mon)
    {
      mon = new StatusMonitor;

      mon->set_name("statuis monitor");
    }


  mon->enter_into_container(root_widget,Point(120,0));
}


void
hide_status_monitor() noexcept
{
  mon->exit_from_container();
}


void
update_status_monitor() noexcept
{
  mon->notify_needing_to_redraw();
}



}




