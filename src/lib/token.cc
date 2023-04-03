#include "ntokenize/token.hh"

namespace ntokenize {
  Token::Token() {
    type = lex::Token::Error;
    pos = {{0,0},{{0,0},{0,0}}};
    value = {string(), string(), string()};
  }

  Token::Token(lex::Token type,
              string value,
              Position pos) {
    type = type;
    value = value;
    pos = pos;
  }

  void Token::clear() {
    type = lex::Token::Error;
    pos.rel = {{0,0},{0,0}};
    value.clear();
  }

  void Token::copy(Token* other) {
    clear();

    type = other->type;
    pos = other->pos;
    value.append(other->value);
  }

  string Token::get_type_name(int16_t ty) {
    return lex::token_name[ty];
  }

  string Token::as_string() {
    char* format = (char*)
      "Token "
      "{\n"
      " type: \"%s\",\n"
      " pos: {\n"
      "  abs: { start: %i, end: %i},\n"
      "  rel: { start: { %i, %i }, end: { %i, %i }},\n"
      " },\n"
      " value: \"%s\" \n"
      "}\n";
    
    string s=string();
    s.reserve(1024);

    sprintf(&s[0], format,
      get_type_name(type).c_str(),
      pos.abs.start, pos.abs.end,
      pos.rel.start.x,pos.rel.start.y,
      pos.rel.end.x,pos.rel.end.y,
      value.raw.c_str()
    );

    return s;
  }

  void Token::Value::clear() {
    prefix.clear();
    raw.clear();
    suffix.clear();
  }

  void Token::Value::append(Value other) {
    prefix.append(other.prefix);
    raw.append(other.raw);
    suffix.append(other.suffix);
  }
} // namespace ntokenize
