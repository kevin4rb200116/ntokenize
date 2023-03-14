#include "tokenize.hh"

namespace tokenize {
  // "0[xX](?:_?[0-9a-fA-F])+"
  Rule(HexNumber) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    switch ((*t->line)[t->end]) {
      case '0':
        t->end++;

        switch ((*t->line)[t->end]) {
          case 'x':
          case 'X':
            t->end += 2;
            break;

          default:
            t->type = lex::token["ERRORTOKEN"];
            t->end = b;
            return false;
        }

        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    for (t->end; t->line->length() > t->end; t->end++) {
      if ((*t->line)[t->end] >= '0')
        if ((*t->line)[t->end] <= '9')
          continue;

      if ((*t->line)[t->end] >= 'a')
        if ((*t->line)[t->end] <= 'f')
          continue;

      if ((*t->line)[t->end] >= 'A')
        if ((*t->line)[t->end] <= 'F')
          continue;

      break;
    }

    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    if (t->raw_value.length() < 3) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // "0[bB](?:_?[01])+"
  Rule(Binnumber) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    switch ((*t->line)[t->end]) {
      case '0':
        t->end++;

        switch ((*t->line)[t->end]) {
          case 'b':
          case 'B':
            t->end += 2;
            break;

          default:
            t->type = lex::token["ERRORTOKEN"];
            t->end = b;
            return false;
        }

        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    for (t->end; t->line->length() > t->end; t->end++) {
      if ((*t->line)[t->end] == '0')
        continue;

      if ((*t->line)[t->end] == '1')
        continue;

      break;
    }

    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    if (t->raw_value.length() < 3) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // "0[oO](?:_?[0-7])+"
  Rule(Octnumber) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    switch ((*t->line)[t->end]) {
      case '0':
        t->end++;

        switch ((*t->line)[t->end]) {
          case 'o':
          case 'O':
            t->end += 2;
            break;

          default:
            t->type = lex::token["ERRORTOKEN"];
            t->end = b;
            return false;
        }

        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    for (t->end; t->line->length() > t->end; t->end++) {
      if ((*t->line)[t->end] >= '0')
        if ((*t->line)[t->end] <= '7')
          continue;

      break;
    }

    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    if (t->raw_value.length() < 3) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // "(?:0(?:_?0)*|[1-9](?:_?[0-9])*)"
  Rule(Decnumber) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    if (!((*t->line)[t->end] >= '0')) {
      if (!((*t->line)[t->end] <= '9')) {
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
      }
    }

    for (t->end; t->line->length() > t->end; t->end++) {
      if ((*t->line)[t->end] >= '0')
        if ((*t->line)[t->end] <= '9')
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

  // "(HexNumber|Binnumber|Octnumber|Decnumber)"
  Rule(Intnumber) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    if (HexNumber(t)) {
      return true;
    }

    t->end = b;

    if (Binnumber(t)) {
      return true;
    }

    t->end = b;

    if (Octnumber(t)) {
      return true;
    }

    t->end = b;

    if (Decnumber(t)) {
      return true;
    }

    t->end = b;

    return false;
  }

  // "[eE][-+]?[0-9](?:_?[0-9])*"
  Rule(Exponent) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    switch ((*t->line)[t->end]) {
      case 'e':
      case 'E':
        t->end++;

        switch ((*t->line)[t->end]) {
          case '-':
          case '+':
            t->end++;
            break;
        }

        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    if (!Decnumber(t)) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    t->end++;
    t->start = b;

    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // ("Decnumber\.Decnumber)?'|r'\.Decnumber)Exponent?
  Rule(Pointfloat) {
    int b = t->end;
    t->start = t->end;

    if (Decnumber(t)) {
      t->end++;
    }

    if ((*t->line)[t->end] != '.') {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    t->end++;

    if (!Decnumber(t)) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    t->end++;

    if (Exponent(t))
      t->end++;

    t->type = lex::token["NUMBER"];
    t->start=b;

    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // "Decnumber+(_Decnumber+)*Exponent"
  Rule(Expfloat) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    if (!Decnumber(t)) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    t->end++;

    if (!Exponent(t)) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    t->end++;
    t->start=b;

    t->raw_value = t->line->substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // (Pointfloat|Expfloat);
  Rule(Floatnumber) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    if (Pointfloat(t))
      return true;

    t->end = b;

    if (Expfloat(t))
      return true;

    t->end = b;

    return false;
  }

  // "([0-9](?:_?[0-9])*[jJ]|(Floatnumber[jJ])"
  Rule(Imagnumber) {
    int b = t->end;
    t->start = t->end;

    if (!Floatnumber(t)) {
      t->type = lex::token["NUMBER"];
      t->end = b;

      if (!Decnumber(t)) {
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
      }
    }

    t->end++;

    switch ((*t->line)[t->end]) {
      case 'j':
      case 'J':
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

  // (Imagnumber|Floatnumber|Intnumber)
  Rule(Number) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    if (Floatnumber(t))
      return true;

    t->end = b;

    if (Imagnumber(t))
      return true;

    t->end = b;

    if (Intnumber(t))
      return true;

    t->end = b;

    return false;
  }
}