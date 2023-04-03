#include "common.hh"
#include "lex.hh"

#ifndef TokenHeader
#define TokenHeader

namespace ntokenize {

  typedef struct Token {
    int16_t type;

    struct Position {
      struct Absolute {
        size_t start,end;
      } abs;

      struct Relative {
        struct { size_t x,y; } start, end;
      } rel;
    } pos;

    struct Value {
      string prefix,raw,suffix;

      void clear();
      void append(Value other);
    } value;

    
    void clear();
    void copy(Token* other);
    string get_type_name(int16_t ty);
    string as_string();

    Token();
    Token(lex::Token type,
              string value,
              Position pos);
  } Token;
} // namespace ntokenize


#endif //TokenHeader