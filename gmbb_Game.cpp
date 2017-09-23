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
  static ButtonState  btnst;

    if(routine_stack.size())
    {
      routine_stack.back()(ctrl);
    }

  else
    if(ctrl.test(p_button_pressed))
    {
      start_main_menu();

      return;
    }


  if(btnst.test(   up_button_pressed) || ctrl.test(up_button_pressed   )){btnst.set(   up_button_pressed);  move_board_view_to_up(   );}
  if(btnst.test( left_button_pressed) || ctrl.test(left_button_pressed )){btnst.set( left_button_pressed);  move_board_view_to_left( );}
  if(btnst.test(right_button_pressed) || ctrl.test(right_button_pressed)){btnst.set(right_button_pressed);  move_board_view_to_right();}
  if(btnst.test( down_button_pressed) || ctrl.test(down_button_pressed )){btnst.set( down_button_pressed);  move_board_view_to_down( );}

  if(ctrl.test(   up_button_released)){btnst.unset(   up_button_pressed);}
  if(ctrl.test( left_button_released)){btnst.unset( left_button_pressed);}
  if(ctrl.test(right_button_released)){btnst.unset(right_button_pressed);}
  if(ctrl.test( down_button_released)){btnst.unset( down_button_pressed);}

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

    for(int  x = 0;  x < game::board_width;  ++x)
    {
      board.get_square(x,                   0).set_kind(game::SquareKind::wall);
      board.get_square(x,game::board_height-1).set_kind(game::SquareKind::wall);
    }


    for(int  y = 1;  y < game::board_height-1;  ++y)
    {
      board.get_square(                  0,y).set_kind(game::SquareKind::wall);
      board.get_square(game::board_width-1,y).set_kind(game::SquareKind::wall);
    }


    for(int  y = 1;  y < game::board_height-1;  ++y){
    for(int  x = 1;  x < game::board_width -1;  ++x){
      board.get_square(x,y).set_kind(game::SquareKind::room);
    }}
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




