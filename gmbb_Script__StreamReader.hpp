#ifndef GMBB_Script__StreamReader_HPP
#define GMBB_Script__StreamReader_HPP


#include"gmbb_Script__Token.hpp"


namespace gmbb{
namespace script{


class
StreamReader
{
  char const*  pointer=nullptr;

  int  line_number=1;

  std::string  read_identifier() noexcept;
  std::string  read_string() noexcept;

  int  read_decimal_integer() noexcept;
  int  read_integer_that_begins_by_zero() noexcept;

  TokenString  read_token_string(char  opening, char  closing) noexcept;

public:
  StreamReader() noexcept{}
  StreamReader(char const*  p) noexcept: pointer(p){}

  void  skip_spaces() noexcept;

  void  advance(int  n) noexcept{pointer += n;}

  char  get_char() const noexcept{return *pointer;}

  Token  operator()() noexcept;

};


}}




#endif




