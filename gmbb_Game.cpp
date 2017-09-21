#include"gmbb_Game_private.hpp"




namespace gmbb{


game::Hero
hero;


game::Board
board;


int
response_value;


void   set_response(int  v) noexcept{response_value = v;}
int    get_response(      ) noexcept{return response_value;}


Image
screen_image(320,240);


GlyphSet
glset;


Widget
root_widget;


bool
screen_is_needing_to_redraw = true;


void
(*current_callback)(Controller const&  ctrl);


void
waiting(Controller const&  ctrl)
{
    if(is_choosing_active())
    {
      process_choosing(ctrl);

      return;
    }


    if(is_message_active())
    {
      process_message(ctrl);

      return;
    }


    if(is_sack_menu_active())
    {
      process_sack_menu(ctrl);

      return;
    }


    if(is_main_menu_active())
    {
      process_main_menu(ctrl);

      return;
    }


    if(ctrl.test(p_button_pressed))
    {
      start_main_menu();
    }
}




Image const&
get_screen_image() noexcept
{
  return screen_image;
}


bool
is_screen_needing_to_redraw() noexcept
{
    if(screen_is_needing_to_redraw)
    {
      screen_is_needing_to_redraw = false;

      return true;
    }


  return false;
}


void
initialize() noexcept
{
  glset.load_from_file("/usr/local/share/gmbb/small_font.bin");

  auto  p = board.new_piece();

  board.set_hero_piece(p);

  current_callback = waiting;

  show_status_monitor();
}


void
step(Controller const&  ctrl)
{
  current_callback(ctrl);

  root_widget.update();

    if(root_widget.is_needing_to_redraw())
    {
      screen_image.fill();

      root_widget.render(screen_image);

      screen_is_needing_to_redraw = true;
    }
}


}




