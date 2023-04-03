#include "ntokenize/main.hh"

namespace ntokenize {
  // '\\~|\\}|\\|=|\\||\\{|\\^=|\\^|\\]|\\[|@=|@|>>=|>>|>=|>|==|=|<=|<<=|<<|<|;|:=|:|/=|//=|//|/|\\.\\.\\.|\\.|\\->|\\-=|\\-|,|\\+=|\\+|\\*=|\\*\\*=|\\*\\*|\\*|\\)|\\(|\\&=|\\&|%=|%|!=)'
  bool Tokenizer::is_special() {
    if (check({'(',lex::Token::LPar}, {')',lex::Token::RPar}))
      return true;

    if (check({'{',lex::Token::LBrace}, {'}',lex::Token::RBrace})) {
      return true;
    }

    if (check({'[',lex::Token::LSQB}, {']',lex::Token::RSQB}))
      return true;

    if (check({'-',lex::Token::Minus})) {
      if (check({'=',lex::Token::MinEqual})
          || check({'>',lex::Token::RArrow}));
      else
        current.type = lex::Token::Minus;

      return true;
    }

    if (check({'*',lex::Token::Star})) {
      if (check({'=',lex::Token::StarEqual})
          || check({'*',lex::Token::DoubleStar}));
      else
        current.type = lex::Token::Star;

      if (current.type == lex::Token::DoubleStar) {
        if (check({'=',lex::Token::DoubleStarEqual}));
        else
          current.type = lex::Token::DoubleStar;
      }

      return true;
    }

    if (check({'/',lex::Token::Slash})) {
      if (check({'=',lex::Token::SlashEqual})
          || check({'/',lex::Token::DoubleSlash}));
      else
        current.type = lex::Token::Slash;

      if (current.type == lex::Token::DoubleSlash) {
        if (check({'=',lex::Token::DoubleSlashEqual}));
        else
          current.type = lex::Token::DoubleSlash;
      }

      return true;
    }

    if (check({'<',lex::Token::Less})) {
      if (check({'=',lex::Token::LessEqual})
          || check({'-',lex::Token::LArrow})
          || check({'<',lex::Token::LShift}));
      else
        current.type = lex::Token::Less;

      if (current.type == lex::Token::LShift) {
        if (check({'=',lex::Token::LShiftEqual}));
        else
          current.type = lex::Token::LShift;
      }

      return true;
    }

    if (check({'>',lex::Token::Greater})) {
      if (check({'=',lex::Token::GreaterEqual})
          || check({'>',lex::Token::RShift}));
      else
        current.type = lex::Token::Greater;

      if (current.type == lex::Token::RShift) {
        if (check({'=',lex::Token::RShiftEqual}));
        else
          current.type = lex::Token::RShift;
      }

      return true;
    }

    if (check({'.',lex::Token::Dot})) {
      if (check({'.',lex::Token::Error})) {
        if (check({'.',lex::Token::Ellipsis}))
          return true;

        return false;
      } else
        current.type = lex::Token::Dot;

      return true;
    }

    if (check({':',lex::Token::Colon})) {
      if (check({'=', lex::Token::ColonEqual}));
      else
        current.type = lex::Token::Colon;

      return true;
    }

    if (check({'+',lex::Token::Plus})) {
      if (check({'=',lex::Token::PlusEqual}));
      else
        current.type = lex::Token::Plus;

      return true;
    }

    if (check({'|',lex::Token::VBar})) {
      if (check({'=',lex::Token::VBarEqual}));
      else
        current.type = lex::Token::VBar;

      return true;
    }

    if (check({'&',lex::Token::Amper})) {
      if (check({'=',lex::Token::AmperEqual}));
      else
        current.type = lex::Token::Amper;

      return true;
    }

    if (check({'=',lex::Token::Equal})) {
      if (check({'=',lex::Token::EQEqual}));
      else
        current.type = lex::Token::Equal;

      return true;
    }

    if (check({'%',lex::Token::Percent})) {
      if (check({'=',lex::Token::PercentEqual}));
      else
        current.type = lex::Token::Percent;

      return true;
    }

    if (check({'^',lex::Token::Circumflex})) {
      if (check({'=',lex::Token::CircumflexEqual}));
      else
        current.type = lex::Token::Circumflex;

      return true;
    }

    if (check({'@',lex::Token::AT})) {
      if (check({'=',lex::Token::ATEqual}));
      else
        current.type = lex::Token::AT;

      return true;
    }

    if (check({'!',lex::Token::Not})) {
      if (check({'=',lex::Token::NotEqual}));
      else
        current.type = lex::Token::Not;

      return true;
    }

    if (check({',', lex::Token::Comma}))
      return true;

    if (check({';', lex::Token::Semi}))
      return true;

    if (check({'~',lex::Token::Tilde}))
      return true;

    current.type = lex::Token::Error;
    return false;
  }
} // namespace tokenize