#include"gmbb_Game_private.hpp"




namespace gmbb{


game::Hero
hero;


game::Board
board;


covered_ptr<game::Piece>
hero_piece;


Image
character_image;


IntervalTimer
interval_timer;


int
response_value;


void   set_response(int  v) noexcept{response_value = v;}
int    get_response(      ) noexcept{return response_value;}


Image
screen_image(screen_width,screen_height);


GlyphSet
glset;


GlyphSet
large_glset;


Widget
root_widget;


bool
screen_is_needing_to_redraw = true;


void
(*current_callback)(Controller const&  ctrl);




uint32_t
flags_for_waiting;




void
wait_until_be_released(uint32_t  flags) noexcept
{
  flags_for_waiting |= flags;
}


bool
is_not_waiting_for(uint32_t  flags) noexcept
{
  return !(flags_for_waiting&flags);
}




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
  using namespace gmbb::flags_of_input;

    if(routine_stack.size())
    {
      routine_stack.back()(ctrl);
    }

  else
    if(ctrl.test(p_button))
    {
    }

  else
    if(ctrl.test(n_button) && is_not_waiting_for(flags_of_input::p_button|flags_of_input::n_button))
    {
      start_main_menu();
    }

  else
    {
        if(interval_timer.check(280,ctrl.get_time()))
        {
               if(ctrl.test(up_button   )){move_hero_piece_to_forward();  interval_timer.enable();}
          else if(ctrl.test(left_button )){turn_hero_piece_to_left( );  interval_timer.enable();}
          else if(ctrl.test(right_button)){turn_hero_piece_to_right();  interval_timer.enable();}
          else if(ctrl.test(down_button )){move_hero_piece_to_backward();  interval_timer.enable();}
          else {interval_timer.disable();}
        }


      board.step();

      update_board_view();
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
  large_glset.load_from_file("/usr/local/share/gmbb/large_font.bin");

  File  f("",File::get_content_from_file("../bin/image.png"));

  auto  r = f.make_reader();

  character_image.load_png(r);

  hero_piece = board.new_piece(2,2);

  hero_piece->reset(hero);

  board.set_hero_piece(hero_piece);

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
  flags_for_waiting &= ctrl.get();


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




