#include "ntokenize/tokenize.hh"

namespace ntokenize {
  // (|RB|u|Rb|Br|b|fr|r|Rf|br|fR|Fr|R|f|rb|FR|BR|rf|bR|rB|B|F|rF|RF|U)
  TRule(string_prefix) {
    current.start = current.end;

    switch (*curr_char) {
      case 'u':
      case 'U':
        break;

      case 'b':
      case 'B':
        step();

        switch (*curr_char) {
          case 'r':
          case 'R':
            step();
            break;

          default:
            break;
        }

        break;

      case 'f':
      case 'F':
        step();

        switch (*curr_char) {
          case 'r':
          case 'R':
            step();
            break;

          default:
            break;
        }

        break;

      case 'r':
      case 'R':
        step();

        switch (*curr_char) {
          case 'b':
          case 'B':
            step();
            break;

          case 'f':
          case 'F':
            step();
            break;

          default:
            break;
        }

        break;

      default:
        current.type = lex::Token::Error;
        return false;
    }

    if (current.value.length() >= 2) {
        current.type = lex::Token::Error;
        return false;
    }

    return true;
  }

  // "[^'\\]*(?:\\.[^'\\]*)*'"
  TRule(single) {
    current.start = current.end;
    current.type = lex::Token::String;

    switch (*curr_char) {
      case '\'':
        step();
        break;

      default:
        current.type = lex::Token::Error;
        return false;
    }

    for (step(); curr_char; step()) {
      if (*curr_char == '\\') {
        step();
        continue;
      }

      if (*curr_char == '\'')
        break;
    }

    switch (*curr_char) {
      case '\'':
        step();
        break;

      default:
        current.type = lex::Token::Error;
        return false;
    }

    return true;
  }

  // "[^\"\\]*(?:\\.[^\"\\]*)*\"\""
  TRule(double) {
    current.start = current.end;
    current.type = lex::Token::String;

    switch (*curr_char) {
      case '"':
        step();
        break;

      default:
        current.type = lex::Token::Error;
        return false;
    }

    for (step(); curr_char; step()) {
      if (*curr_char == '\\') {
        step();
        continue;
      }

      if (*curr_char == '"')
        break;
    }

    switch (*curr_char) {
      case '"':
        step();
        break;

      default:
        current.type = lex::Token::Error;
        return false;
    }

    return true;
  }

/*
  // "[^'\\]*(?:(?:\\.|'(?!''))[^'\\]*)*'''"
  TRule(single3) {
    current.start = current.end;
    current.type = lex::Token::String;

    if (*curr_char != '\'') {
      step();
      if ((*t->line)[t->end+1] != '\'') {
        if ((*t->line)[t->end+2] != '\'') {
          current.type = lex::Token::Error;
          return false;
        }
      }
    }

    t->end += 3;

    for (t->end; t->line->length() > t->end; t->end++) {
      if (*curr_char == '\\')
        t->end += 2;

      if (*curr_char == '\'')
        if ((*t->line)[t->end+1] == '\'')
          if ((*t->line)[t->end+2] == '\'')
            break;
    }

    if (*curr_char != '\'') {
      if ((*t->line)[t->end+1] != '\'') {
        if ((*t->line)[t->end+2] != '\'') {
          t->type = lex::token["ERRORTOKEN"];
          t->end = b;
          return false;
        }
      }
    }

    t->end += 3;

    t->start = b;
    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    if (t->raw_value.length() < 6) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // "[^\"\\]*(?:(?:\\.|\"(?!\"\"))[^\"\\]*)*\"\"\""
  Rule(Double3) {
    int b = t->end;
    t->start = t->end;

    t->type = lex::token["STRING"];

    if (*curr_char != '"') {
      if ((*t->line)[t->end+1] != '"') {
        if ((*t->line)[t->end+2] != '"') {
          t->type = lex::token["ERRORTOKEN"];
          t->end = b;
          return false;
        }
      }
    }

    t->end += 3;

    for (t->end; t->line->length() > t->end; t->end++) {
      if (*curr_char == '\\')
        t->end += 2;

      if (*curr_char == '"')
        if ((*t->line)[t->end+1] == '"')
          if ((*t->line)[t->end+2] == '"')
            break;
    }

    if (*curr_char != '"') {
      if ((*t->line)[t->end+1] != '"') {
        if ((*t->line)[t->end+2] != '"') {
          t->type = lex::token["ERRORTOKEN"];
          t->end = b;
          return false;
        }
      }
    }

    t->end += 3;

    t->start = b;
    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    if (t->raw_value.length() < 6) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // (StringPrefix\'\'\'|StringPrefix\"\"\")
  Rule(Triple) {
    int b = t->end;
    t->start = t->end;

    if (StringPrefix(t))
      t->end++;

    if (Single3(t)) {
      t->end++;
      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Double3(t)) {
      t->end++;
      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    return false;
  }
*/

  // '(StringPrefix*(Single|Double)
  TRule(string) {
    auto b = current.end;
    current.start = current.end;
    current.type = lex::Token::String;

    is_string_prefix();

    if (is_single()) {
      current.start = b;
      return true;
    }

    if (is_double()) {
      current.start = b;
      return true;
    }

    return false;
  }

/*
  // "StringPrefix*(Triple|String)"
  Rule(ContStr) {
    int b = t->end;
    t->start = t->end;

    if (StringPrefix(t))
      t->end++;

    if (!Triple(t)) {
      if (!String(t)) {
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
      }
    }

    t->end++;

    t->start = b;
    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }
*/
} // namespace tokenize
