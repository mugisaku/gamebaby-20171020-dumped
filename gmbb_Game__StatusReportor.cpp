#include"gmbb_Game_private.hpp"


namespace gmbb{


namespace{


class
StatusReportor: public Window
{
public:
  void  render(Image&  dst) noexcept override;

} *rep;


void
StatusReportor::
render(gmbb::Image&  dst) noexcept
{
  Window::render(dst);

  char  buf[256];

  auto  hero_p = board.get_hero_piece();

  static Pixel  const  pixels[] = {Pixel(null),Pixel(white),Pixel(null),Pixel(null)};

  Point  pt = rectangle;

  pt.x += 8;
  pt.y += 8;

  snprintf(buf,sizeof(buf),"けん");

  dst.print(buf,pt,glset,pixels);

  pt.y += glset.get_height();


  snprintf(buf,sizeof(buf),"たて");

  dst.print(buf,pt,glset,pixels);

  pt.y += glset.get_height();


  snprintf(buf,sizeof(buf),"おび");

  dst.print(buf,pt,glset,pixels);

  pt.y += glset.get_height();


}


}


void
show_status_reportor() noexcept
{
    if(!rep)
    {
      rep = new StatusReportor;

      rep->resize(300,80);
    }


  rep->enter_into(root_widget,Point(8,160));

  rep->set_state(WindowState::full_opened);
}


void
hide_status_reportor() noexcept
{
  rep->leave_from_parent();
}




}




