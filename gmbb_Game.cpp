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




std::vector<Routine>
routine_stack;


void
push_routine(Routine  r) noexcept
{
  routine_stack.emplace_back(r);
}


void
pop_routine(Routine  r) noexcept
{
    while(routine_stack.size())
    {
      auto  bk = routine_stack.back();

      routine_stack.pop_back();

        if(bk == r)
        {
          break;
        }
    }
}




void
waiting(Controller const&  ctrl)
{
    if(routine_stack.size())
    {
      routine_stack.back()(ctrl);
    }

  else
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

  p->reset(hero);

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


//  root_widget.print();

//  printf("\n");
}


}




