#include "common.hh"
#include "lex.hh"

#ifndef TokenizeHeader
#define TokenizeHeader

#define Rule(name) bool is_##name()
#define TRule(name) bool Tokenizer::is_##name()

namespace ntokenize {
  using namespace std;

  typedef struct File {
    protected:
      FILE* fp;

    public:
      unique_ptr<char> read_char();
      unique_ptr<string> read_line();
      unique_ptr<string> read_file();

      File(FILE* fp) 
        : fp(fp) {}
  } File;

  typedef struct Token {
    int16_t type;
    pair<size_t,size_t> start, end;
    string value;

    string as_string();
    void clear();
    void copy(Token* other);
    static unique_ptr<Token> from(Token* other);

    Token()
      : type(lex::Token::Error), value(string()), start({0,0}), end({0,0}) {}

    Token(lex::Token type,
              string value, pair<size_t,size_t> start, pair<size_t,size_t> end)
      : type(type), value(value), start(start), end(end) {}
  } Token;

  typedef struct Tokenizer {
    File file;
    unique_ptr<char> curr_char;
    Token last,current;

    void eat();
    void step();
    void next();

    Tokenizer(FILE* fp)
      : file(File(fp)) {}

    Rule(whitespace);
    Rule(comment);
    Rule(ignore);
    Rule(name);
    Rule(hex_number);
    Rule(bin_number);
    Rule(oct_number);
    Rule(dec_number);
    Rule(int_number);
    Rule(exponent);
    Rule(point_float);
    Rule(exp_float);
    Rule(float_number);
    Rule(imag_number);
    Rule(number);
    Rule(string_prefix);
    Rule(single); // single quoted string
    Rule(double); // double quoted string
    // Rule(single3);
    // Rule(double3);
    // Rule(triple);
    Rule(string);
    Rule(cont_str);
    Rule(special);
    Rule(funny);
    Rule(plain_token);
    Rule(token);
    Rule(pseudo_extras);
    Rule(pseudo_token);

    private:
      inline Rule(paren);
      inline Rule(square_brace);
      inline Rule(colon);
      inline Rule(comma);
      inline Rule(semi);
      inline Rule(plus);
      inline Rule(minus);
      inline Rule(star);
      inline Rule(slash);
      inline Rule(vbar);
      inline Rule(amper);
      inline Rule(less);
      inline Rule(greater);
      inline Rule(equal);
      inline Rule(dot);
      inline Rule(percent);
      inline Rule(brace);
      inline Rule(tilde);
      inline Rule(circumflex);
      inline Rule(at);
      inline Rule(exclamation);
  } Tokenizer;
}

#endif

