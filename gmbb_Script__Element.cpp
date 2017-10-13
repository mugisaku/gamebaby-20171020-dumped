#include"gmbb_Script__Element.hpp"




namespace gmbb{
namespace script{




void
ElementList::
print(int  indent) const noexcept
{
  printf("{\n");

  auto      it = cbegin();
  auto  end_it =   cend();

    if(it != end_it)
    {
      it++->print(indent+1);

        while(it != end_it)
        {
          printf("  ");

          it++->print(indent+1);
        }
    }


  printf("\n");

    for(int  n = 0;  n < indent;  ++n)
    {
      printf("  ");
    }


  printf("}\n");
}




ElementList
read_element_list(TokenString const&  toks) noexcept
{
  ElementList  ls;

  auto   it = toks.cbegin();
  auto  end = toks.cend();

    while(it != end)
    {
        if(*it == TokenKind::identifier)
        {
          auto&  id = *it++;

            if((it != end) && (*it == TokenKind::token_string))
            {
              auto&  subtok = *it++;

              ls.emplace_back(id->string,read_element_list(subtok->token_string));
            }

          else
            {
              ls.emplace_back(id);
            }
        }

      else
        {
          ls.emplace_back(*it++);
        }
    }


  return std::move(ls);
}


void
Element::
print(int  indent) const noexcept
{
    for(int  n = 0;  n < indent;  ++n)
    {
      printf("  ");
    }


  printf("%s",name.data());

    if(token){token.print();}
  else       {elements.print(indent);}
}




}}




