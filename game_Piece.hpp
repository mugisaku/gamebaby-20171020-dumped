#ifndef game_Piece_HPP
#define game_Piece_HPP


#include"game_Hero.hpp"
#include"game_Enemy.hpp"
#include"game_Board.hpp"
#include"gmbb_Figures.hpp"
#include"gmbb_Image.hpp"
#include<covered_ptr>


namespace game{


enum class
PieceKind
{
  null,
  hero,
  friend_hero,
  enemy,

};


union
PieceData
{
  covered_ptr<Hero>    hero;
  covered_ptr<Enemy>  enemy;

   PieceData(){}
  ~PieceData(){}
};


struct
Attribute
{
  static constexpr int    human = 0x001;
  static constexpr int    beast = 0x002;
  static constexpr int   spirit = 0x004;
  static constexpr int    plant = 0x008;
  static constexpr int  machine = 0x010;
  static constexpr int    flyer = 0x020;
  static constexpr int   undead = 0x040;
  static constexpr int   insect = 0x080;
  static constexpr int    shell = 0x100;
  static constexpr int  aquatic = 0x200;
  static constexpr int   dragon = 0x400;

};


class Square;
class Piece;


enum class
PieceFlag
{
  no_animation = 0x1,
  blink        = 0x2,
  invisible    = 0x4,

};


struct
Action
{
  using Callback = void  (*)(Piece&  actor, int  count) noexcept;

  Callback  callback;

  int  count;

  constexpr Action(Callback  cb, int  c=0) noexcept:
  callback(cb),
  count(c){}

};


class
Piece
{
  using UpdateCallback = void  (*)(Piece&  p) noexcept;
  using RenderCallback = void  (*)(Piece const&  p, gmbb::Image&  dst, gmbb::Point  dst_point) noexcept;


  covered_ptr<Board>    board;
  covered_ptr<Square>  square;

  PieceLink  link;

  PieceKind  kind=PieceKind::null;
  PieceData  data;

  char16_t const*  name;

  int  hp    ;
  int  hp_max;

  UpdateCallback  update_callback=nullptr;
  RenderCallback  render_callback=nullptr;

  Direction  moving_direction;
  Direction    face_direction;

  gmbb::Point  rendering_point;

  int  action_index=0;
  int   frame_index=0;
  int   frame_count=0;

  int     sleep_count=0;
  int      seal_count=0;
  int    poison_count=0;
  int   confuse_count=0;
  int     blind_count=0;
  int  illusion_count=0;

  covered_ptr<SackItem>   sword_item;
  covered_ptr<SackItem>  shield_item;
  covered_ptr<SackItem>    belt_item;

  std::vector<Action>  action_stack;

public:
  Piece(Board&  brd) noexcept: board(&brd){}
  Piece(Piece const&  rhs) noexcept=delete;
  Piece(Piece&&       rhs) noexcept=delete;

  Piece&  operator=(Piece const&  rhs) noexcept=delete;
  Piece&  operator=(Piece&&       rhs) noexcept=delete;

  void  reset(Hero&   hero) noexcept;
  void  reset(Enemy&  enem) noexcept;

  void                 set_square(covered_ptr<Square>  sq)       noexcept{       square = sq;}
  covered_ptr<Square>  get_square(                       ) const noexcept{return square     ;}


  int  get_hp()     const noexcept{return hp    ;}
  int  get_hp_max() const noexcept{return hp_max;}

  void  set_rendering_point_by_current_square(int  square_size) noexcept;

  void  set_rendering_point(gmbb::Point  pt) noexcept{rendering_point = pt;}

  void  move_rendering_point(int  x, int  y) noexcept{rendering_point += gmbb::Point(x,y);}

  gmbb::Point  get_rendering_point() const noexcept{return rendering_point;}

  void  set_direction(       Direction  d)       noexcept{moving_direction = face_direction = d;}
  void  set_moving_direction(Direction  d) noexcept{moving_direction = d;}
  void  set_face_direction(  Direction  d) noexcept{  face_direction = d;}

  void  turn_face_direction_to_left(    ) noexcept{face_direction = get_right(   face_direction);}
  void  turn_face_direction_to_right(   ) noexcept{face_direction = get_left(    face_direction);}
  void  turn_face_direction_to_opposite() noexcept{face_direction = get_opposite(face_direction);}

  Direction  get_moving_direction() const noexcept{return moving_direction;}
  Direction  get_face_direction(  ) const noexcept{return   face_direction;}

  void    hold_item(covered_ptr<SackItem>  p) noexcept;
  bool  unhold_item(covered_ptr<SackItem>  p) noexcept;

  void  unhold_sword() noexcept;
  void  unhold_shield() noexcept;
  void  unhold_belt() noexcept;

  covered_ptr<SackItem>  get_sword_item()  const noexcept{return  sword_item;}
  covered_ptr<SackItem>  get_shield_item() const noexcept{return shield_item;}
  covered_ptr<SackItem>  get_belt_item()   const noexcept{return   belt_item;}


  void  reset_frame() noexcept;

  void  increase_frame_index_when_over(int  limit) noexcept;

  int  get_frame_index() const noexcept{return frame_index;}
  int  get_frame_count() const noexcept{return frame_count;}


  void  change_action_index(int  v) noexcept;
  int  get_action_index() const noexcept{return action_index;}

  Board&  get_board() const noexcept{return *board;}

  PieceLink&  get_link() noexcept{return link;}

  Piece const*  get_previous() const noexcept{return link.get_previous();}
  Piece const*  get_next()     const noexcept{return link.get_next();}

  void  push_action(Action::Callback  cb, int  count=0) noexcept{action_stack.emplace_back(cb,count);}

  bool  is_busy() const noexcept{return action_stack.size();}

  void  set_update_callback(UpdateCallback  cb) noexcept{update_callback = cb;}
  void  set_render_callback(RenderCallback  cb) noexcept{render_callback = cb;}

  void  step() noexcept;

  void  render(gmbb::Image&  dst, gmbb::Point  offset) const noexcept{render_callback(*this,dst,rendering_point-offset);}

};


}




#endif




