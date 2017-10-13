#include"gmbb_Game_private.hpp"


namespace gmbb{


namespace{


class
StatusMonitor: public Actor
{
public:
  void  render(Image&  dst, Point  offset) const noexcept;

} *mon;


void
StatusMonitor::
render(gmbb::Image&  dst, Point  offset) const noexcept
{
  char  buf[256];

  snprintf(buf,sizeof(buf),"HP%3d/%3d",hero_piece->get_hp(),hero_piece->get_hp_max());

  dst.print(buf,get_relative_point()+offset,glset);
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


  mon->enter_into_group(root_widget,Point(120,0));
}


void
hide_status_monitor() noexcept
{
  mon->exit_from_group();
}


void
update_status_monitor() noexcept
{
  mon->notify_needing_to_redraw();
}



}




