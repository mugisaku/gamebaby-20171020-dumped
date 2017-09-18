#include"gmbb_Game.hpp"




namespace gmbb{


Image
screen_image(320,240);


GlyphSet
glset;


Widget
root_widget;


MenuWindow*
main_menu_window;


MessageWindow*
message_window;


constexpr Point  message_point(8,160);




bool
screen_is_needing_to_redraw = true;


void
(*current_callback)(Controller const&  ctrl);


void  operate_main_menu(Controller const&  ctrl);
void    operate_message(Controller const&  ctrl);
void            waiting(Controller const&  ctrl);


void
operate_message(Controller const&  ctrl)
{
  static bool  pressing;

    if(ctrl.test(p_button_pressed))
    {
      pressing = true;
    }


    if(message_window->is_stopped())
    {
        if(pressing)
        {
          message_window->scroll();

          return;
        }
    }


    if(ctrl.test(p_button_released))
    {
      pressing = false;
    }


  auto  now = ctrl.get_time();

  constexpr uint32_t  interval_time_base = 200;

  auto  interval_time = interval_time_base;

  static uint32_t  last_time;

    if(pressing)
    {
      interval_time /= 5;
    }


    if(now > (last_time+interval_time))
    {
      last_time = now;

      message_window->step();
    }
}


void
operate_main_menu(Controller const&  ctrl)
{
    if(ctrl.test(p_button_pressed))
    {
      constexpr int        talk = 0;
      constexpr int  belongings = 1;
      constexpr int        foot = 2;
      constexpr int   interrupt = 3;

      auto  i = main_menu_window->get_item_index();

        switch(i)
        {
      case(talk):
          message_window->enter_into(root_widget,message_point);

          message_window->set_state(WindowState::open_to_down);

          message_window->push(u"その　ほうこうには　だれもいない");
          break;
      default:;
          break;
        }
    }

  else
    if(ctrl.test(n_button_pressed))
    {
      main_menu_window->reset_cursor();

      main_menu_window->set_state(WindowState::close_to_up);
    }

  else
    if(ctrl.test(up_button_pressed))
    {
      main_menu_window->move_cursor_to_up();
    }

  else
    if(ctrl.test(down_button_pressed))
    {
      main_menu_window->move_cursor_to_down();
    }

  else
    if(ctrl.test(left_button_pressed))
    {
      main_menu_window->move_cursor_to_left();
    }

  else
    if(ctrl.test(right_button_pressed))
    {
      main_menu_window->move_cursor_to_right();
    }
}


void
waiting(Controller const&  ctrl)
{
    if(message_window->get_parent())
    {
        if((*message_window == WindowState::open_to_down) ||
           (*message_window == WindowState::close_to_up ))
        {
          message_window->animate();
        }

      else
        if(*message_window == WindowState::full_opened)
        {
            if(message_window->is_remaining())
            {
              operate_message(ctrl);
            }

          else
            if(ctrl.test(p_button_pressed))
            {
                if(message_window->is_clean())
                {
                  message_window->set_state(WindowState::close_to_up);
                }

              else
                {
                  message_window->clear();
                }
            }

          else
            if(ctrl.test(p_button_released))
            {
              message_window->clear();
            }
        }

      else
        if(*message_window == WindowState::hidden)
        {
          message_window->leave_from_parent();
        }


      return;
    }


    if(main_menu_window->get_parent())
    {
        if((*main_menu_window == WindowState::open_to_down) ||
           (*main_menu_window == WindowState::close_to_up))
        {
          main_menu_window->animate();
        }

      else
        if(*main_menu_window == WindowState::full_opened)
        {
          operate_main_menu(ctrl);
        }

      else
        if(*main_menu_window == WindowState::hidden)
        {
          main_menu_window->leave_from_parent();
        }


      return;
    }


    if(ctrl.test(p_button_pressed))
    {
      main_menu_window->enter_into(root_widget,Point(8,8));

      main_menu_window->set_state(WindowState::open_to_down);
    }
}


void
cb(Image&  dst, Point  point, int  i)
{
  Pixel  pixels[] = {predefined_color_index::null,predefined_color_index::white};

  char  buf[32];

  snprintf(buf,sizeof(buf),"%3d",i);

  dst.print(to_u16string(buf).data(),point,glset,pixels);
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
create_main_menu_window() noexcept
{
    if(main_menu_window)
    {
      return;
    }


  Menu  menu(glset.get_width()*5,glset.get_height(),2,2);

  main_menu_window = new MenuWindow(menu,[](Image&  dst, Point  point, int  i)
    {
      Pixel  pixels[] = {Pixel(null),Pixel(white),Pixel(null),Pixel(null)};

      static char16_t const*  text_table[] = {
        u"はなす",u"もちもの",
        u"あしもと",u"ちゅうだん",
      };


      dst.print(text_table[i],point,glset,pixels);
    });



}


void
create_message_window() noexcept
{
    if(message_window)
    {
      return;
    }


  message_window = new MessageWindow(glset,36,4);
}


void
initialize() noexcept
{
  glset.load_from_file("/usr/local/share/gmbb/small_font.bin");

  create_main_menu_window();
  create_message_window();

  current_callback = waiting;
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




