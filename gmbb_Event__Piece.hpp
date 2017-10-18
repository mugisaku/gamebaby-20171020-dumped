#ifndef GMBB_Event__Piece_HPP
#define GMBB_Event_Piece_HPP


#include"covered_ptr"


namespace gmbb{


class Piece;


enum class
PieceEventKind
{
  null,
  talk,
  push,
  start_move,
  end_move,

};


enum class
PieceEventSubKind: int;


struct
PieceEvent
{
  PieceEventKind         kind;
  PieceEventSubKind  sub_kind;

  covered_ptr<Piece>  piece;
  covered_ptr<Piece>  guest;

  PieceEvent(PieceEventKind  k, covered_ptr<Piece>  piece_, covered_ptr<Piece>  guest_) noexcept:
  kind(k),
  piece(piece_), guest(guest_){}

};


}




#endif




