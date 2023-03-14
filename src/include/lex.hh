#include "common.hh"

#ifndef LexHeader
#define LexHeader

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

#endif //LexHeader
