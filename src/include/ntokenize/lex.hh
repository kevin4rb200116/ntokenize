#include "common.hh"

#ifndef LexHeader
#define LexHeader

namespace ntokenize::lex {
  using namespace std;

  typedef enum Token : int16_t {
    EndMarker,
    Name,

    Number,
    BinNumber,
    OctNumber,
    DecNumber,
    HexNumber,
    FloatNumber,
    ImagNumber,

    String,
    SingleString,
    DoubleString,
    Single3String,
    Double3String,
    TripleString,

    NewLine,
    Indent,
    Dedent,
    LPar,
    RPar,
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
    Not,
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
    RShiftEqual,
    DoubleStarEqual,
    DoubleSlash,
    DoubleSlashEqual,
    AT,
    ATEqual,
    RArrow,
    LArrow,
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

  extern map<int16_t,string> token_name;
}

#endif //LexHeader