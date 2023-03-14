#include "tokenize.hh"

namespace tokenize {
  // (|RB|u|Rb|Br|b|fr|r|Rf|br|fR|Fr|R|f|rb|FR|BR|rf|bR|rB|B|F|rF|RF|U)
  Rule(StringPrefix) {
    int b = t->end;
    t->start = t->end;

    switch ((*t->line)[t->end]) {
      case 'u':
      case 'U':
        break;

      case 'b':
      case 'B':
        t->end++;

        switch ((*t->line)[t->end]) {
          case 'r':
          case 'R':
            t->end++;
            break;
          
          default:
            break;
        }

        break;

      case 'f':
      case 'F':
        t->end++;

        switch ((*t->line)[t->end]) {
          case 'r':
          case 'R':
            t->end++;
            break;
          
          default:
            break;
        }

        break;

      case 'r':
      case 'R':
        t->end++;

        switch ((*t->line)[t->end]) {
          case 'b':
          case 'B':
            t->end++;
            break;

          case 'f':
          case 'F':
            t->end++;
            break;
          
          default:
            break;
        }

        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    t->end = b;

    if (!Name(t)) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    if (t->raw_value.length() > 2) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // "[^'\\]*(?:\\.[^'\\]*)*'"
  Rule(Single) {
    int b = t->end;
    t->start = t->end;

    t->type = lex::token["STRING"];

    switch ((*t->line)[t->end]) {
      case '\'':
        t->end++;
        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    for (t->end; t->line->length() > t->end; t->end++) {
      if ((*t->line)[t->end] == '\\')
        t->end += 2;

      if ((*t->line)[t->end] == '\'')
        break;
    }

    switch ((*t->line)[t->end]) {
      case '\'':
        t->end++;
        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    t->start = b;
    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // "[^\"\\]*(?:\\.[^\"\\]*)*\"\""
  Rule(Double) {
    int b = t->end;
    t->start = t->end;

    t->type = lex::token["STRING"];

    switch ((*t->line)[t->end]) {
      case '"':
        t->end++;
        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    for (t->end; t->line->length() > t->end; t->end++) {
      if ((*t->line)[t->end] == '\\')
        t->end += 2;

      if ((*t->line)[t->end] == '"')
        break;
    }

    switch ((*t->line)[t->end]) {
      case '"':
        t->end++;
        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    t->start = b;
    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // "[^'\\]*(?:(?:\\.|'(?!''))[^'\\]*)*'''"
  Rule(Single3) {
    int b = t->end;
    t->start = t->end;

    t->type = lex::token["STRING"];

    if ((*t->line)[t->end] != '\'') {
      if ((*t->line)[t->end+1] != '\'') {
        if ((*t->line)[t->end+2] != '\'') {
          t->type = lex::token["ERRORTOKEN"];
          t->end = b;
          return false;
        }
      }
    }

    t->end += 3;

    for (t->end; t->line->length() > t->end; t->end++) {
      if ((*t->line)[t->end] == '\\')
        t->end += 2;

      if ((*t->line)[t->end] == '\'')
        if ((*t->line)[t->end+1] == '\'')
          if ((*t->line)[t->end+2] == '\'')
            break;
    }

    if ((*t->line)[t->end] != '\'') {
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

    if ((*t->line)[t->end] != '"') {
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
      if ((*t->line)[t->end] == '\\')
        t->end += 2;

      if ((*t->line)[t->end] == '"')
        if ((*t->line)[t->end+1] == '"')
          if ((*t->line)[t->end+2] == '"')
            break;
    }

    if ((*t->line)[t->end] != '"') {
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

  // '(StringPrefix*(Single|Double)
  Rule(String) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["STRING"];

    if (StringPrefix(t))
      t->end++;

    if (Single(t)) {
      t->end++;

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Double(t)) {
      t->end++;

      t->start = b;
      t->raw_value = t->line->substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    return false;
  }

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
} // namespace tokenize
