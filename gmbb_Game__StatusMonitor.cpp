#include"gmbb_Game_private.hpp"


namespace gmbb{


namespace{


class
StatusMonitor: public Widget
{
public:
  void  render(Image&  dst) noexcept;

} *mon;


void
StatusMonitor::
render(gmbb::Image&  dst) noexcept
{
  char  buf[256];

  auto  hero_p = board.get_hero_piece();

  snprintf(buf,sizeof(buf),"HP%3d/%3d",hero_p->get_hp(),hero_p->get_hp_max());

  static Pixel  const  pixels[] = {Pixel(null),Pixel(white),Pixel(null),Pixel(null)};

  dst.print(buf,rectangle,glset,pixels);
}


}


void
show_status_monitor() noexcept
{
    if(!mon)
    {
      mon = new StatusMonitor;
    }


  mon->enter_into(root_widget,Point(120,0));
}


void
hide_status_monitor() noexcept
{
  mon->leave_from_parent();
}




}



