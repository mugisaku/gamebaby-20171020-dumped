#include"gmbb_Game_private.hpp"


namespace gmbb{


namespace{


class
StatusReportor: public Window
{
public:
  void  render(Image&  dst, Point  dst_point) const noexcept override;

} *rep;


void
StatusReportor::
render(gmbb::Image&  dst, Point  dst_point) const noexcept
{
  Window::render(dst,dst_point);

  char  buf[256];

  auto&  hero_p = *board.get_hero_piece();

  Point  pt = dst_point;

  auto  w = glset.get_width();
  auto  h = glset.get_height();

  pt.x += 8;
  pt.y += 8;

  auto   sword = hero_p.get_sword_item();
  auto  shield = hero_p.get_shield_item();
  auto    belt = hero_p.get_belt_item();

  dst.print(u"けん",pt,glset);

    if(sword)
    {
      dst.print((*sword)->get_name(),pt+Point(w*3),glset);
    }


  pt.y += h;

  dst.print(u"たて",pt,glset);

    if(shield)
    {
      dst.print((*shield)->get_name(),pt+Point(w*3),glset);
    }


  pt.y += h;

  dst.print(u"おび",pt,glset);

    if(belt)
    {
      dst.print((*belt)->get_name(),pt+Point(w*3),glset);
    }


  pt.y += h;


}


}


void
show_status_reportor() noexcept
{
    if(!rep)
    {
      rep = new StatusReportor;

      rep->resize(300,80);

      rep->set_name("status repoter");
    }


  rep->enter_into_container(root_widget,Point(8,160));

  rep->set_state(WindowState::full_opened);
}


void
hide_status_reportor() noexcept
{
  rep->exit_from_container();
}


void
update_status_reportor() noexcept
{
  rep->notify_needing_to_redraw();
}


}




