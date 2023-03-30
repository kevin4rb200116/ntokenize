#include "common.hh"
#include "lex.hh"

#ifndef TokenizeHeader
#define TokenizeHeader

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

    Token();
    Token(lex::Token type,
              string value, pair<size_t,size_t> start, pair<size_t,size_t> end);
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

    bool is_whitespace();
    bool is_comment();
    bool is_ignore();
    bool is_name();
    bool is_hex_number();
    bool is_bin_number();
    bool is_oct_number();
    bool is_dec_number();
    bool is_exponent();
    bool is_point_float();
    bool is_number();
    bool is_string_prefix();
    bool is_single();
    bool is_double();
    bool is_string();
    bool is_special();
    bool is_funny();
    bool is_plain_token();
    bool is_token();

    private:
      inline bool is_paren();
      inline bool is_square_brace();
      inline bool is_colon();
      inline bool is_comma();
      inline bool is_semi();
      inline bool is_plus();
      inline bool is_minus();
      inline bool is_star();
      inline bool is_slash();
      inline bool is_vbar();
      inline bool is_amper();
      inline bool is_less();
      inline bool is_greater();
      inline bool is_equal();
      inline bool is_dot();
      inline bool is_percent();
      inline bool is_brace();
      inline bool is_tilde();
      inline bool is_circumflex();
      inline bool is_at();
      inline bool is_exclamation();
  } Tokenizer;
}

#endif

