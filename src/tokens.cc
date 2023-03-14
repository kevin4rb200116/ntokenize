#include "tokenize.hh"

namespace tokenize {
  // "[ \f\t]*"
  Rule(Whitespace) {
    int b=t->end;
    t->start = t->end;

    t->type = lex::token["TYPE_IGNORE"];

    switch ((*t->line)[t->end]) {
      case ' ':
      case '\f':
      case '\t':
        t->end++;
        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    for (t->end; t->end <= t->line->length(); t->end++) {
      switch ((*t->line)[t->end]) {
        case ' ':
        case '\f':
        case '\t':
          continue;

        default:
          break;
      }

      break;
    }

    t->start = b;
    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // "#[^\r\n]*"
  Rule(Comment) {
    int b=t->end;
    t->start = t->end;
    t->type = lex::token["COMMENT"];

    if ((*t->line)[t->end] != '#') {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    for (t->end; t->end <= t->line->length(); t->end++) {
      switch ((*t->line)[t->end]) {
        case '\r':
        case '\n':
          break;

        default:
          continue;
      }

      break;
    }

    switch ((*t->line)[t->end]) {
      case '\r':
      case '\n':
        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    //t->end = t->line->length();

    t->start = b;
    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    t->type = lex::token["COMMENT"];

    return true;
  }

  // Whitespace(Funny|Whitespace)Comment?
  Rule(Ignore) {
    int end = t->end;

    if (Whitespace(t))
      return true;

    t->end = end;

    if (Funny(t))
      return true;

    t->end = end;

    if (Comment(t))
      return true;

    t->end = end;

    return false;
  }

  // "\w+"
  Rule(Name) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NAME"];

    if (!isalpha((*t->line)[t->end])) {
      if ((*t->line)[t->end] != '_') {
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
      }
    }

    t->end++;

    for (t->end; t->end <= t->line->length(); t->end++) {
      if (isalnum((*t->line)[t->end]))
        continue;

      if ((*t->line)[t->end] == '_')
        continue;

      break;
    }

    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    if (t->raw_value.length() == 0) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // "\r?\n(Special)"
  Rule(Funny) {
    int b = t->end;
    t->start = t->end;

    if (Special(t))
      return true;

    t->end = b;

    t->type = lex::token["NL"];

    if ((*t->line)[t->end] == '\r')
      t->end++;

    if (!((*t->line)[t->end] == '\n')) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    t->end++;
    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // (Funny|Number|Name|ContStr)
  Rule(PlainToken) {
    int b = t->end;
    t->start = t->end;

    if (Number(t))
      return true;

    t->end = b;

    if (Funny(t))
      return true;

    t->end = b;

    if (String(t))
      return true;

    t->end = b;

    if (Name(t))
      return true;

    t->end = b;

    return false;
  }

  // (Ignore|PlainToken)
  Rule(Token) {
    int b = t->end;
    t->start = t->end;

    if (Ignore(t))
      return true;

    t->end = b;

    if (PlainToken(t))
      return true;

    t->end = b;

    return false;
  }

  // (Whitespace|Comment|Triple)
  Rule(PseudoExtras) {
    int b = t->end;
    t->start = t->end;

    if (Whitespace(t))
      return true;

    t->end = b;

    if (Comment(t))
      return true;

    t->end = b;

    if (Triple(t))
      return true;

    t->end = b;

    return false;
  }

  // Whitespace(PseudoExtras|Token)
  Rule(PseudoToken) {
    int b = t->end;
    t->start = t->end;

    if (Whitespace(t))
      return true;

    t->end = b;

    if (PseudoExtras(t))
      return true;

    t->end = b;

    if (Token(t))
      return true;

    t->end = b;

    return false;
  }
}