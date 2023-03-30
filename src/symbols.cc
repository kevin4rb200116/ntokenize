#include "ntokenize/tokenize.hh"

namespace ntokenize {
  inline bool Tokenizer::is_paren() {
    switch (*curr_char) {
      case '(':
        current.type = lex::Token::LPar;
        step();
        return true;

      case ')':
        current.type = lex::Token::Rpar;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_square_brace() {
    switch (*curr_char) {
      case '[':
        current.type = lex::Token::LSQB;
        step();
        return true;

      case ']':
        current.type = lex::Token::RSQB;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_colon() {
    switch (*curr_char) {
      case ':':
        current.type = lex::Token::Colon;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_comma() {
    switch (*curr_char) {
      case ',':
        current.type = lex::Token::Comma;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_semi() {
    switch (*curr_char) {
      case ';':
        current.type = lex::Token::Semi;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_plus() {
    switch (*curr_char) {
      case '+':
        current.type = lex::Token::Plus;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_minus() {
    switch (*curr_char) {
      case '-':
        current.type = lex::Token::Minus;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_star() {
    switch (*curr_char) {
      case '*':
        current.type = lex::Token::Star;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_slash() {
    switch (*curr_char) {
      case '/':
        current.type = lex::Token::Slash;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_vbar() {
    switch (*curr_char) {
      case '|':
        current.type = lex::Token::VBar;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_amper() {
    switch (*curr_char) {
      case '&':
        current.type = lex::Token::Amper;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_less() {
    switch (*curr_char) {
      case '<':
        current.type = lex::Token::Less;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_greater() {
    switch (*curr_char) {
      case '>':
        current.type = lex::Token::Greater;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_equal() {
    switch (*curr_char) {
      case '=':
        current.type = lex::Token::Equal;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_dot() {
    switch (*curr_char) {
      case '.':
        current.type = lex::Token::Dot;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_percent() {
    switch (*curr_char) {
      case '%':
        current.type = lex::Token::Percent;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_brace() {
    switch (*curr_char) {
      case '{':
        current.type = lex::Token::LBrace;
        step();
        return true;

      case '}':
        current.type = lex::Token::RBrace;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_tilde() {
    switch (*curr_char) {
      case '~':
        current.type = lex::Token::Tilde;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_circumflex() {
    switch (*curr_char) {
      case '^':
        current.type = lex::Token::Circumflex;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_at() {
    switch (*curr_char) {
      case '@':
        current.type = lex::Token::AT;
        step();
        return true;

      default:
        return false;
    }
  }

  inline bool Tokenizer::is_exclamation() {
    switch (*curr_char) {
      case '!':
        step();
        return true;

      default:
        return false;
    }
  }

  // '\\~|\\}|\\|=|\\||\\{|\\^=|\\^|\\]|\\[|@=|@|>>=|>>|>=|>|==|=|<=|<<=|<<|<|;|:=|:|/=|//=|//|/|\\.\\.\\.|\\.|\\->|\\-=|\\-|,|\\+=|\\+|\\*=|\\*\\*=|\\*\\*|\\*|\\)|\\(|\\&=|\\&|%=|%|!=)'
  bool Tokenizer::is_special() {
    current.start = current.end;
    current.type = lex::Token::Operator;

    if (is_paren())
      return true;

    if (is_square_brace())
      return true;

    if (is_colon()) {
      if (is_equal())
        current.type = lex::Token::ColonEqual;

      return true;
    }

    if (is_comma())
      return true;

    if (is_semi())
      return true;

    if (is_plus()) {
      if (is_equal())
        current.type = lex::Token::PlusEqual;

      return true;
    }

    if (is_minus()) {
        if (is_equal() || is_greater()) {
          if (current.type == lex::Token::Equal)
            current.type = lex::Token::MinEqual;
          if (current.type == lex::Token::Greater)
            current.type = lex::Token::RArrow;
        }

      return true;
    }

    if (is_star()) {
      if (is_equal() || is_star()) {
        if (current.type == lex::Token::Equal)
          current.type = lex::Token::StarEqual;

        if (current.type == lex::Token::Star) {
          current.type = lex::Token::DoubleStar;

          if (is_equal()) {
            current.type = lex::Token::DoubleStarEqual;
          }
        }
      }

      return true;
    }

    if (is_slash()) {
      if (is_equal() || is_slash()) {
        if (current.type == lex::Token::Equal)
          current.type = lex::Token::SlashEqual;

        if (current.type == lex::Token::Slash) {
          current.type = lex::Token::DoubleSlash;

          if (is_equal())
            current.type = lex::Token::DoubleSlashEqual;
        }
      }

      return true;
    }

    if (is_vbar()) {
      if (is_equal())
        current.type = lex::Token::VBarEqual;

      return true;
    }

    if (is_amper()) {
      if (is_equal())
        current.type = lex::Token::AmperEqual;

      return true;
    }

    if (is_less()) {
      if (is_equal() || is_less()) {
        if (current.type == lex::Token::Equal)
          current.type = lex::Token::LessEqual;

        if (current.type == lex::Token::Less) {
          current.type = lex::Token::LShift;

          if (is_equal())
            current.type = lex::Token::LShiftEqual;
        }
      }

      return true;
    }

    if (is_greater()) {
      if (is_equal() || is_greater()) {
        if (current.type == lex::Token::Equal)
          current.type = lex::Token::GreaterEqual;

        if (current.type == lex::Token::Greater) {
          current.type = lex::Token::RShift;

          if (is_equal()) {
            current.type = lex::Token::RshiftEqual;
          }
        }
      }

      return true;
    }

    if (is_equal()) {
      if (is_equal())
        current.type = lex::Token::EQEqual;

      return true;
    }

    if (is_dot()) {
      if (is_dot())
        if (is_dot())
          current.type = lex::Token::Ellipsis;

      return true;
    }

    if (is_percent()) {
      if (is_equal())
        current.type = lex::Token::PercentEqual;

      return true;
    }

    if (is_brace())
      return true;

    if (is_tilde())
      return true;

    if (is_circumflex()) {
      if (is_equal())
        current.type = lex::Token::CircumflexEqual;

      return true;
    }

    if (is_at()) {
      if (is_equal())
        current.type = lex::Token::ATEqual;

      return true;
    }

    if (is_exclamation()) {
      if (is_equal())
        current.type = lex::Token::NotEqual;

      return true;
    }

    current.type = lex::Token::Error;
    return false;
  }
} // namespace tokenize
