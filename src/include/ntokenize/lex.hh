#include "common.hh"

#ifndef LexHeader
#define LexHeader

namespace ntokenize::lex {
  using namespace std;

  typedef enum Token : int16_t {
    EndMarker,
    Name,
    Number,
    String,
    NewLine,
    Indent,
    Dedent,
    LPar,
    Rpar,
    LSQB,
    RSQB,
    Colon,
    Comma,
    Semi,
    Plus,
    Minus,
    Star,
    Slash,
    VBar,
    Amper,
    Less,
    Greater,
    Equal,
    Dot,
    Percent,
    LBrace,
    RBrace,
    EQEqual,
    NotEqual,
    LessEqual,
    GreaterEqual,
    Tilde,
    Circumflex,
    LShift,
    RShift,
    DoubleStar,
    PlusEqual,
    MinEqual,
    StarEqual,
    SlashEqual,
    PercentEqual,
    AmperEqual,
    VBarEqual,
    CircumflexEqual,
    LShiftEqual,
    RshiftEqual,
    DoubleStarEqual,
    DoubleSlash,
    DoubleSlashEqual,
    AT,
    ATEqual,
    RArrow,
    Ellipsis,
    ColonEqual,
    Operator,
    Await,
    Async,
    Ignore,
    SoftKeyword,
    Error,
    Comment,
    N_TOKENS,
    NT_OFFSET = 256,
  } Token;

  extern map<Token,string> token_name;

/*
  typedef map<string,int> TokenList;
  typedef map<int,string> TokenNameList;
  typedef map<string,string> OperatorList;

  extern TokenNameList token_name;
  extern OperatorList _operator;
  extern TokenList token;
  extern TokenList EXACT_TOKEN_TYPE;
*/
}

#endif //LexHeader
