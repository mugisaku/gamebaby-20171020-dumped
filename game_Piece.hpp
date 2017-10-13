#ifndef game_Piece_HPP
#define game_Piece_HPP


#include"gmbb.hpp"
#include"game_Hero.hpp"
#include"game_Enemy.hpp"
#include"game_Square.hpp"


namespace gmbb{


enum class
PieceKind
{
  null,
  hero,
  friend_hero,
  enemy,

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


class Board;


class
Piece: public PieceBase
{
  covered_ptr<Board>  board;

  PieceKind  kind=PieceKind::null;

  int  hp    ;
  int  hp_max;

  int     sleep_count=0;
  int      seal_count=0;
  int    poison_count=0;
  int   confuse_count=0;
  int     blind_count=0;
  int  illusion_count=0;

  covered_ptr<SackItem>   sword_item;
  covered_ptr<SackItem>  shield_item;
  covered_ptr<SackItem>    belt_item;

public:
  Piece(Board&  brd) noexcept: board(&brd){}
  Piece(Piece const&) noexcept=delete;
  Piece(Piece&&     ) noexcept=delete;


  Piece&  operator=(Piece const&) noexcept=delete;
  Piece&  operator=(Piece&&     ) noexcept=delete;

  void  reset(Hero&   hero) noexcept;
  void  reset(Enemy&  enem) noexcept;


  int  get_hp()     const noexcept{return hp    ;}
  int  get_hp_max() const noexcept{return hp_max;}

  void    hold_item(covered_ptr<SackItem>  p) noexcept;
  bool  unhold_item(covered_ptr<SackItem>  p) noexcept;

  void  unhold_sword() noexcept;
  void  unhold_shield() noexcept;
  void  unhold_belt() noexcept;

  covered_ptr<SackItem>  get_sword_item()  const noexcept{return  sword_item;}
  covered_ptr<SackItem>  get_shield_item() const noexcept{return shield_item;}
  covered_ptr<SackItem>  get_belt_item()   const noexcept{return   belt_item;}

  void  set_controll_callback(ControllCallback<Piece>  cb) noexcept
  {controll_callback = reinterpret_cast<ControllCallback<EffectObject>>(cb);}

  void  set_render_callback(RenderCallback<Piece>  cb) noexcept
  {render_callback = reinterpret_cast<RenderCallback<EffectObject>>(cb);}


  Board&  get_board() const noexcept{return *board;}

  void  set_position_by_current_square() noexcept;

};




}




#endif




