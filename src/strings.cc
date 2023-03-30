#include "ntokenize/tokenize.hh"

namespace ntokenize {
  // (|RB|u|Rb|Br|b|fr|r|Rf|br|fR|Fr|R|f|rb|FR|BR|rf|bR|rB|B|F|rF|RF|U)
  bool Tokenizer::is_string_prefix() {
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
  bool Tokenizer::is_single() {
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
  bool Tokenizer::is_double() {
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

  // '(StringPrefix*(Single|Double)
  bool Tokenizer::is_string() {
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
} // namespace tokenize
