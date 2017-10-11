#include"gmbb_Script__TokenString.hpp"
#include"gmbb_Script__Token.hpp"
#include"gmbb_Script__StreamReader.hpp"




namespace gmbb{
namespace script{




TokenString::
TokenString(char const*  filepath) noexcept
{
  auto  f = fopen(filepath,"rb");

    if(f)
    {
      std::string  s;

        for(;;)
        {
          auto  c = fgetc(f);

            if(feof(f) || ferror(f))
            {
              break;
            }


          s += c;
        }


      fclose(f);


      StreamReader  sr(s.data());

      assign(sr);
    }
}




void
TokenString::
assign(StreamReader&  reader, char  op, char  cl) noexcept
{
  clear();

  opening = op;
  closing = cl;

    for(;;)
    {
      reader.skip_spaces();

        if(reader.get_char() == cl)
        {
          reader.advance(1);

          break;
        }


      auto  tok = reader();

        if(!tok)
        {
          break;
        }


      emplace_back(std::move(tok));
    }
}




void
TokenString::
print() const noexcept
{
    if(opening){printf("%c",opening);}


    for(auto&  tok: *this)
    {
      tok.print();

      printf(" ");
    }


    if(closing){printf("%c",closing);}
}


}}




