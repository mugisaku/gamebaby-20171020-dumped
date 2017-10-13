#include"gmbb_Game_private.hpp"


namespace gmbb{


namespace{


void
process_new_piece(Director&  di, script::ElementList const&  ls) noexcept
{
  std::string const*  name=nullptr;

  int  x = 0;
  int  y = 0;

    for(auto&  e: ls)
    {
        if(e.name == "name")
        {
          name = &e.elements[0].token->string;
        }

      else
        if(e.name == "type")
        {
          e.elements[0].token.print();
        }

      else
        if(e.name == "initial_position")
        {
          x = e.elements[0].token->integer;
          y = e.elements[1].token->integer;
        }
    }


//  auto  p = board.new_piece(x,y);
}


void
process_new(Director&  di, script::ElementList const&  ls) noexcept
{
    for(auto&  e: ls)
    {
        if(e.name == "Piece")
        {
          process_new_piece(di,e.elements);
        }
    }
}


}


void
process_script(Director&  di, script::Element const&  e)
{
    if(e.name == "new")
    {
      process_new(di,e.elements);
    }
}




}




