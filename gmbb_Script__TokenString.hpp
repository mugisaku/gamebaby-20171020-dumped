#ifndef GMBB_Script__TokenString_HPP
#define GMBB_Script__TokenString_HPP


#include<vector>


namespace gmbb{
namespace script{


class Token;
class StreamReader;


class
TokenString: public std::vector<Token>
{
  char  opening=0;
  char  closing=0;

public:
  TokenString() noexcept{}
  TokenString(StreamReader&  reader, char  op=0, char  cl=0){assign(reader,op,cl);}
  TokenString(char const*  filepath);

  void  assign(StreamReader&  reader, char  op=0, char  cl=0);

  char  get_opening() const noexcept{return opening;}
  char  get_closing() const noexcept{return closing;}

  void  print() const noexcept;

};


}}




#endif




