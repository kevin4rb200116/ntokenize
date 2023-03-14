#include "ntokenize/tokenize.hh"

namespace ntokenize {
  inline Rule(Paren) {
    switch (((*t->line)[t->end])) {
      case '(':
        t->type = lex::token["LPAR"];
        t->end++;
        return true;

      case ')':
        t->type = lex::token["RPAR"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(SquareBrace) {
    switch (((*t->line)[t->end])) {
      case '[':
        t->type = lex::token["LSQB"];
        t->end++;
        return true;

      case ']':
        t->type = lex::token["RSQB"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Colon) {
    switch (((*t->line)[t->end])) {
      case ':':
        t->type = lex::token["COLON"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Comma) {
    switch (((*t->line)[t->end])) {
      case ',':
        t->type = lex::token["COMMA"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Semi) {
    switch (((*t->line)[t->end])) {
      case ';':
        t->type = lex::token["SEMI"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Plus) {
    switch (((*t->line)[t->end])) {
      case '+':
        t->type = lex::token["PLUS"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Minus) {
    switch (((*t->line)[t->end])) {
      case '-':
        t->type = lex::token["MINUS"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Star) {
    switch (((*t->line)[t->end])) {
      case '*':
        t->type = lex::token["STAR"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Slash) {
    switch (((*t->line)[t->end])) {
      case '/':
        t->type = lex::token["SLASH"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(VBar) {
    switch (((*t->line)[t->end])) {
      case '|':
        t->type = lex::token["VBAR"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Amper) {
    switch (((*t->line)[t->end])) {
      case '&':
        t->type = lex::token["AMPER"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Less) {
    switch (((*t->line)[t->end])) {
      case '<':
        t->type = lex::token["LESS"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Greater) {
    switch (((*t->line)[t->end])) {
      case '>':
        t->type = lex::token["GREATER"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Equal) {
    switch (((*t->line)[t->end])) {
      case '=':
        t->type = lex::token["EQUAL"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Dot) {
    switch (((*t->line)[t->end])) {
      case '.':
        t->type = lex::token["DOT"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Percent) {
    switch (((*t->line)[t->end])) {
      case '%':
        t->type = lex::token["PERCENT"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Brace) {
    switch (((*t->line)[t->end])) {
      case '{':
        t->type = lex::token["LBRACE"];
        t->end++;
        return true;

      case '}':
        t->type = lex::token["RBRACE"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Tilde) {
    switch (((*t->line)[t->end])) {
      case '~':
        t->type = lex::token["TILDE"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Circumflex) {
    switch (((*t->line)[t->end])) {
      case '^':
        t->type = lex::token["CIRCUMFLEX"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(At) {
    switch (((*t->line)[t->end])) {
      case '@':
        t->type = lex::token["AT"];
        t->end++;
        return true;

      default:
        return false;
    }
  }

  inline Rule(Exclamation) {
    switch (((*t->line)[t->end])) {
      case '!':
        t->end++;
        return true;

      default:
        return false;
    }
  }

  // '\\~|\\}|\\|=|\\||\\{|\\^=|\\^|\\]|\\[|@=|@|>>=|>>|>=|>|==|=|<=|<<=|<<|<|;|:=|:|/=|//=|//|/|\\.\\.\\.|\\.|\\->|\\-=|\\-|,|\\+=|\\+|\\*=|\\*\\*=|\\*\\*|\\*|\\)|\\(|\\&=|\\&|%=|%|!=)'
  Rule(Special) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["OP"];

    if (Paren(t)) {
      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (SquareBrace(t)) {
      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Colon(t)) {
      if (Equal(t))
        t->type = lex::token["COLONEQUAL"];

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Comma(t)) {
      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Semi(t)) {
      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Plus(t)) {
      if (Equal(t))
        t->type = lex::token["PLUSEQUAL"];

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Minus(t)) {
        if (Equal(t) || Greater(t))
          if (t->type == lex::token["EQUAL"])
            t->type = lex::token["MINEQUAL"];
          if (t->type == lex::token["GREATER"])
            t->type = lex::token["RARROW"];

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Star(t)) {
      if (Equal(t) || Star(t)) {
        if (t->type == lex::token["EQUAL"])
          t->type = lex::token["STAREQUAL"];

        if (t->type == lex::token["STAR"]) {
          t->type = lex::token["DOUBLESTAR"];

          if (Equal(t)) {
            t->type = lex::token["DOUBLESTAREQUAL"];
          }
        }
      }

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Slash(t)) {
      if (Equal(t) || Slash(t)) {
        if (t->type == lex::token["EQUAL"])
          t->type = lex::token["SLASHEQUAL"];

        if (t->type == lex::token["SLASH"]) {
          t->type = lex::token["DOUBLESLASH"];

          if (Equal(t)) {
            t->type = lex::token["DOUBLESLASHEQUAL"];
          }
        }
      }

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (VBar(t)) {
      if (Equal(t))
        t->type = lex::token["VBAREQUAL"];

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Amper(t)) {
      if (Equal(t))
        t->type = lex::token["AMPEREQUAL"];

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Less(t)) {
      if (Equal(t) || Less(t)) {
        if (t->type == lex::token["EQUAL"])
          t->type = lex::token["LESSEQUAL"];

        if (t->type == lex::token["LESS"]) {
          t->type = lex::token["LEFTSHIFT"];

          if (Equal(t)) {
            t->type = lex::token["LEFTSHIFTEQUAL"];
          }
        }
      }

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Greater(t)) {
      if (Equal(t) || Greater(t)) {
        if (t->type == lex::token["EQUAL"])
          t->type = lex::token["GREATEREQUAL"];

        if (t->type == lex::token["GREATER"]) {
          t->type = lex::token["RIGHTSHIFT"];

          if (Equal(t)) {
            t->type = lex::token["RIGHTSHIFTEQUAL"];
          }
        }
      }

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Equal(t)) {
      if (Equal(t))
        t->type = lex::token["EQEQUAL"];

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Dot(t)) {
      if (Dot(t))
        if (Dot(t))
          lex::token["ELLIPSIS"];

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Percent(t)) {
      if (Equal(t))
        t->type = lex::token["PERCENTEQUAL"];

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Brace(t)) {
      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Tilde(t)) {
      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Circumflex(t)) {
      if (Equal(t))
        t->type = lex::token["CIRCUMFLEXEQUAL"];

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (At(t)) {
      if (Equal(t))
        t->type = lex::token["ATEQUAL"];

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Exclamation(t)) {
      if (Equal(t))
        t->type = lex::token["NOTEQUAL"];

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    t->type = lex::token["ERRORTOKEN"];
    t->end = b;

    return false;
  }
} // namespace tokenize
