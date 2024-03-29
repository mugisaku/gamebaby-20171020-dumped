#include"gmbb.hpp"
#include"gmbb_Game.hpp"


using namespace gmbb::script;


int
main(int  argc, char**  argv)
{
  TokenString  toks;

    try
    {
      toks = TokenString("../script.sc");
    }


    catch(StreamError const&  err)
    {
      err.print();

      printf("\n");

      return -1;
    }

    catch(...)
    {
      printf("...\n");

      return -1;
    }


  Element  el("",read_element_list(toks));

  el.print();


  return 0;
}




