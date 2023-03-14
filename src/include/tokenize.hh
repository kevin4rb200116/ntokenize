#include "common.hh"
#include "lex.hh"

#ifndef TokenizeHeader
#define TokenizeHeader

#define Rule(name) bool name(TokenInfo* t)

namespace tokenize {
  using namespace std;

  typedef struct TokenInfo {
    int type, start, end;
    string raw_value;
    string* line;

    int exact_type();
    void from(TokenInfo* t);

    void dump(bool with_line);

    TokenInfo()
      : type(0), raw_value(string()), start(0), end(0), line(nullptr) {}

    TokenInfo(int type, string raw_value, int start, int end, string* line)
      : type(type), raw_value(raw_value), start(start), end(end), line(line) {}
  } TokenInfo;

  typedef struct Tokenizer {
    FILE* fp;
    string line;
    TokenInfo last,current;

    TokenInfo* next();

    Tokenizer(FILE* fp)
      : fp(fp), line(string()) {
      current.line = &line;
    }

  } Tokenizer;

  string read_line(FILE* fp);
  string read_file(FILE* fp);

  Rule(Whitespace);
  Rule(Comment);
  Rule(Ignore);
  Rule(Name);
  Rule(HexNumber);
  Rule(Binnumber);
  Rule(Octnumber);
  Rule(Decnumber);
  Rule(Intnumber);
  Rule(Exponent);
  Rule(Pointfloat);
  Rule(Expfloat);
  Rule(Floatnumber);
  Rule(Imagnumber);
  Rule(Number);
  Rule(StringPrefix);
  Rule(Single);
  Rule(Double);
  Rule(Single3);
  Rule(Double3);
  Rule(Triple);
  Rule(String);
  Rule(ContStr);
  Rule(Special);
  Rule(Funny);
  Rule(PlainToken);
  Rule(Token);
  Rule(PseudoExtras);
  Rule(PseudoToken);
}

#endif

