#include "common.hh"

#ifndef TokenizeHeader
#define TokenizeHeader

namespace lex {
  using namespace std;

  typedef map<string,int> TokenList;
  typedef map<int,string> TokenNameList;
  typedef map<string,string> OperatorList;

  extern TokenNameList token_name;
  extern OperatorList _operator;
  extern TokenList token;
  extern TokenList EXACT_TOKEN_TYPE;
}

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

  bool Whitespace(TokenInfo* i);
  bool Comment(TokenInfo* t);
  bool Ignore(TokenInfo* t);
  bool Name(TokenInfo* t);
  bool HexNumber(TokenInfo* t);
  bool Binnumber(TokenInfo* t);
  bool Octnumber(TokenInfo* t);
  bool Decnumber(TokenInfo* t);
  bool Intnumber(TokenInfo* t);
  bool Exponent(TokenInfo* t);
  bool Pointfloat(TokenInfo* t);
  bool Expfloat(TokenInfo* t);
  bool Floatnumber(TokenInfo* t);
  bool Imagnumber(TokenInfo* t);
  bool Number(TokenInfo* t);
  bool StringPrefix(TokenInfo* t);
  bool Single(TokenInfo* t);
  bool Double(TokenInfo* t);
  bool Single3(TokenInfo* t);
  bool Double3(TokenInfo* t);
  bool Triple(TokenInfo* t);
  bool String(TokenInfo* t);
  bool ContStr(TokenInfo* t);
  bool Special(TokenInfo* t);
  bool Funny(TokenInfo* t);
  bool PlainToken(TokenInfo* t);
  bool Token(TokenInfo* t);
  bool PseudoExtras(TokenInfo* t);
  bool PseudoToken(TokenInfo* t);
}

#endif

