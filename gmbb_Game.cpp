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
screen_image(screen_width,screen_height);


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
pop_routine() noexcept
{
    if(routine_stack.size())
    {
      routine_stack.pop_back();
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

  else if(ctrl.test(up_button_pressed)   ){move_board_view_to_up();}
  else if(ctrl.test(left_button_pressed) ){move_board_view_to_left();}
  else if(ctrl.test(right_button_pressed)){move_board_view_to_right();}
  else if(ctrl.test(down_button_pressed) ){move_board_view_to_down();}
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

  auto  p = board.new_piece(0,0);

  p->reset(hero);

  board.set_hero_piece(p);

  current_callback = waiting;

  show_board_view();
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




