#ifndef GMBB_Script__Element_HPP
#define GMBB_Script__Element_HPP


#include"gmbb_Script__Token.hpp"
#include"gmbb_Script__TokenString.hpp"
#include"gmbb_Script__StreamReader.hpp"


namespace gmbb{
namespace script{


class Element;


class
ElementList: public std::vector<Element>
{
public:
  void  print(int  indent=0) const noexcept;

};


struct
Element
{
  std::string  name;

  Token  token;

  ElementList  elements;


  Element() noexcept{}
  Element(Token const&  tok) noexcept: token(tok){}
  Element(std::string const&  name_, ElementList&&  els) noexcept:
  name(name_), elements(std::move(els)){}

  void  print(int  indent=0) const noexcept;

};


ElementList  read_element_list(TokenString const&  toks) noexcept;

}}




#endif




