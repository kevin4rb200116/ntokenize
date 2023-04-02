#include "common.hh"
#include "lex.hh"

#ifndef TokenizeHeader
#define TokenizeHeader

namespace ntokenize {
  using namespace std;

  typedef struct File {
    FILE* fp;

    unique_ptr<char> read_char();
    File(FILE* fp) : fp(fp) {}
  } File;

  typedef struct Token {
    int16_t type;
    size_t abs_start, abs_end;
    pair<size_t,size_t> start, end;
    string value;

    void clear();
    void copy(Token* other);
    static unique_ptr<Token> from(Token* other);

    Token();
    Token(lex::Token type,
              string value,
              pair<size_t,size_t> start, pair<size_t,size_t> end);
  } Token;

  typedef struct Tokenizer {
    File file;
    unique_ptr<char> curr_char;
    Token last,current;

    void eat();
    void step();
    void next();

    bool check(pair<char,lex::Token> x); // single := x
    bool check(pair<char,lex::Token> x, pair<char,lex::Token> y); // pair := x || y
    bool check(char a, char b, lex::Token T); // range := (a <= x && x <= b)
    bool check(bool (*test)(char), lex::Token T); // tested := test(x)

    Tokenizer(FILE* fp)
      : file(File(fp)) {}

    bool is_whitespace();
    bool is_comment();
    bool is_ignore();
    bool is_name();
    bool is_number();
    bool is_string_prefix();
    bool is_string();
    bool is_special();
    bool is_funny();
    bool is_plain_token();
    bool is_token();
  } Tokenizer;

  inline pair<bool,lex::Token>
    compare(char x, pair<char,lex::Token> a, pair<char,lex::Token> b);
  inline pair<bool,lex::Token>
    compare(char x, pair<char,lex::Token> y);
}

#endif