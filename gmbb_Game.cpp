#include"gmbb_Game_private.hpp"




namespace gmbb{


Hero
hero;


Board
board;


covered_ptr<Piece>
hero_piece;


Image
character_image;


IntervalTimer
interval_timer;


Image
screen_image(screen_width,screen_height);


GlyphSet
glset;


GlyphSet
large_glset;


GadgetContainer
root_widget;


bool
screen_is_needing_to_redraw = true;




void
return_(int  retval) noexcept
{
    if(is_main_menu_window_opened())
    {
      close_main_menu_window();

      hide_status_reportor();
    }
}


void
waiting(Controller const&  ctrl) noexcept
{
  using namespace gmbb::flags_of_input;

  auto  ok = !is_hero_busy();

    if(ok && ctrl.test(p_button))
    {
    }

  else
    if(ok && ctrl.test(n_button))
    {
      open_main_menu_window();

      start_main_menu();

      show_status_reportor();
    }

  else
    {
        if(ok && interval_timer.check(280,ctrl.get_time()))
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
#ifdef EMSCRIPTEN
        glset.load_from_file("small_font.bin");
  large_glset.load_from_file("large_font.bin");

  File  f("",File::get_content_from_file("image.png"));
#else
        glset.load_from_file("/usr/local/share/gmbb/small_font.bin");
  large_glset.load_from_file("/usr/local/share/gmbb/large_font.bin");

  File  f("",File::get_content_from_file("../bin/image.png"));
#endif


  auto  r = f.make_reader();

  character_image.load_png(r);

  Piece::set_source_image(character_image);

  hero_piece = board.new_piece(1,1);
  hero_piece->set_position_by_current_square();

  hero_piece->set_controll_callback(controll_hero_piece);
  hero_piece->set_render_callback(render_hero_piece);

  board.set_hero_piece(hero_piece);

  push_routine(waiting,return_);

  show_board_view();
  show_status_monitor();

    for(int  x = 0;  x < board_width;  ++x)
    {
      board.get_square(x,             0).set_kind(SquareKind::wall);
      board.get_square(x,board_height-1).set_kind(SquareKind::wall);
    }


    for(int  y = 1;  y < board_height-1;  ++y)
    {
      board.get_square(            0,y).set_kind(SquareKind::wall);
      board.get_square(board_width-1,y).set_kind(SquareKind::wall);
    }


    for(int  y = 1;  y < board_height-1;  ++y){
    for(int  x = 1;  x < board_width -1;  ++x){
      board.get_square(x,y).set_kind(SquareKind::room);
    }}


  append_enemy();
}


void
step(Controller const&  ctrl)
{
    if(!has_active_effect_object())
    {
      call_routine(ctrl);
    }


  root_widget.update();

  update_effect();

    if(root_widget.is_needing_to_redraw() || has_active_effect_object())
    {
      screen_image.fill();

      root_widget.render(screen_image,Point());

      render_effect();

      screen_is_needing_to_redraw = true;
    }


//  root_widget.print();

//  printf("\n");
}


}




