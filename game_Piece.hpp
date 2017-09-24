#ifndef game_Piece_HPP
#define game_Piece_HPP


#include"game_Hero.hpp"
#include"game_Enemy.hpp"
#include"game_Board.hpp"
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


class
Piece
{
  covered_ptr<Board>    board;
  covered_ptr<Square>  square;

  PieceLink  link;

  PieceKind  kind=PieceKind::null;
  PieceData  data;

  char16_t const*  name;

  int  hp    ;
  int  hp_max;

  Direction  direction;

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

  void       set_direction(Direction  d)       noexcept{direction = d;}
  Direction  get_direction(            ) const noexcept{return direction;}

  void  change_equipment(covered_ptr<SackItem>  p) noexcept;

  covered_ptr<SackItem>  get_sword_item()  const noexcept{return  sword_item;}
  covered_ptr<SackItem>  get_shield_item() const noexcept{return shield_item;}
  covered_ptr<SackItem>  get_belt_item()   const noexcept{return   belt_item;}

  Board&  get_board() const noexcept{return *board;}

  PieceLink&  get_link() noexcept{return link;}

};


}




#endif




