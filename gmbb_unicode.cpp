#include"gmbb_unicode.hpp"




namespace gmbb{


size_t
utf8_byte_number(unsigned char  c)
{
       if(!(c>>7)             ){return 1;}
  else if( (c>>1) == 0b1111110){return 6;}
  else if( (c>>2) == 0b111110 ){return 5;}
  else if( (c>>3) == 0b11110  ){return 4;}
  else if( (c>>4) == 0b1110   ){return 3;}
  else if( (c>>5) == 0b110    ){return 2;}
  else if( (c>>6) == 0b10     ){return 1;}

  printf("%dはUTF8の先頭ではありません\n",c);

  throw not_utf8();
}


namespace{
int
decode(int  c, int  shift_amount=0) noexcept
{
  return((c&0b111111)<<shift_amount);
}
int
encode(int  c, int  shift_amount=0) noexcept
{
  return((c>>shift_amount)&0b111111);
}
}


char32_t
to_char32(const char*  utf8, size_t  byte_number)
{
  char32_t  c = 0;

    switch(byte_number)
    {
  case(1): c = ((utf8[0]        )    )                                  ;break;
  case(2): c = ((utf8[0]&0b11111)<< 6)|decode(utf8[1])                  ;break;
  case(3): c = ((utf8[0]&0b01111)<<12)|decode(utf8[1],6)|decode(utf8[2]);break;

  case(4):
    c = ((utf8[0]&0b111)<<18)|decode(utf8[1],12)|
                              decode(utf8[2], 6)|
                              decode(utf8[3]   );
    break;
  case(5):
    c = ((utf8[0]&0b11)<<24)|decode(utf8[1],18)|
                             decode(utf8[2],12)|
                             decode(utf8[3], 6)|
                             decode(utf8[4]   );
    break;
  case(6):
    c = ((utf8[0]&0b1)<<30)|decode(utf8[1],24)|
                            decode(utf8[2],18)|
                            decode(utf8[3],12)|
                            decode(utf8[4], 6)|
                            decode(utf8[5]   );
    break;
  default:
      printf("不正なUTF8のバイト数です(%d)\n",byte_number);

      throw invalid_utf8_byte_number();
    }


  return c;
}




std::string
to_string(char16_t const*  u16s)
{
  std::string  s;

    while(*u16s)
    {
      s += UTF8Chunk(*u16s++).codes;
    }


  return std::move(s);
}


std::u16string
to_u16string(char const*  s)
{
  std::u16string  u16s;

    while(*s)
    {
      auto  byte_number = utf8_byte_number(*s);

      u16s += to_char32(s,byte_number);

      s += byte_number;
    }


  return std::move(u16s);
}




int
u16vsnprintf(char16_t*  buf, size_t  n, char const* fmt, va_list  ap)
{
  char  cbuf[2048];

  int  res = vsnprintf(cbuf,sizeof(cbuf),fmt,ap);

    if(res < (n/sizeof(char16_t)))
    {
      char const*  p = cbuf;

        while(*p)
        {
          auto  byte_number = utf8_byte_number(*p);

          *buf++ = to_char32(p,byte_number);

          p += byte_number;
        }


      *buf = 0;

      return res;
    }


  return -1;
}


int
u16snprintf(char16_t*  buf, size_t  n, char const* fmt, ...)
{
  va_list  ap;
  va_start(ap,fmt);

  auto  res = u16vsnprintf(buf,n,fmt,ap);

  va_end(ap);


  return res;
}




UTF8Chunk::
UTF8Chunk(char32_t  c)
{
  *this = c;
}


UTF8Chunk&
UTF8Chunk::
operator=(char32_t  c)
{
  char*  p = codes;

    if(c <= 0x7F)
    {
      *p++ = c;
    }

  else
    if((c >= 0x0080) &&
       (c <= 0x07FF))
    {
      *p++ = (0b11000000|(c>>6));
      *p++ = (0b10000000|encode(c));
    }

  else
    if((c >= 0x0800) &&
       (c <= 0xFFFF))
    {
      *p++ = (0b11100000|(c>>12));
      *p++ = (0b10000000|encode(c,6));
      *p++ = (0b10000000|encode(c  ));
    }

  else
    if((c >= 0x010000) &&
       (c <= 0x1FFFFF))
    {
      *p++ = (0b11110000|(c>>18));
      *p++ = (0b10000000|encode(c,12));
      *p++ = (0b10000000|encode(c, 6));
      *p++ = (0b10000000|encode(c   ));
    }

  else
    if((c >= 0x0200000) &&
       (c <= 0x3FFFFFF))
    {
      *p++ = (0b11111000|(c>>24));
      *p++ = (0b10000000|encode(c,18));
      *p++ = (0b10000000|encode(c,12));
      *p++ = (0b10000000|encode(c, 6));
      *p++ = (0b10000000|encode(c   ));
    }

  else
    if((c >= 0x04000000) &&
       (c <= 0x7FFFFFFF))
    {
      *p++ = (0b11111100|(c>>30));
      *p++ = (0b10000000|encode(c,24));
      *p++ = (0b10000000|encode(c,18));
      *p++ = (0b10000000|encode(c,12));
      *p++ = (0b10000000|encode(c, 6));
      *p++ = (0b10000000|encode(c   ));
    }

  else
    {
      printf("%dはユニコードではありません\n",c);

      throw not_utf32();
    }


  *p = 0;

  return *this;
}


}




