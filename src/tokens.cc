#include "ntokenize/tokenize.hh"

namespace ntokenize {
  // "[ \f\t]*"
  TRule(whitespace) {
    current.start = current.end;
    current.type = lex::Token::Ignore;

    switch (*curr_char) {
      case '\f':
        current.value.append("\\f");
        curr_char = file.read_char();
        break;

      case '\t':
        current.value.append("\\r");
        curr_char = file.read_char();
        break;

      case ' ':
        step();
        break;

      default:
        current.type = lex::Token::Error;
        return false;
    }

    for (; curr_char;) {
      switch (*curr_char) {
        case '\f':
          current.value.append("\\f");
          curr_char = file.read_char();
          break;

        case '\t':
          current.value.append("\\r");
          curr_char = file.read_char();
          break;

        case ' ':
          step();
          break;

        default:
          break;
      }

      break;
    }

    return true;
  }

  // "#[^\r\n]*"
  TRule(comment) {
    current.start = current.end;
    current.type = lex::Token::Comment;

    if (*curr_char != '#') {
      current.type = lex::Token::Error;
      return false;
    }

    for (; curr_char; step()) {
      switch (*curr_char) {
        default:
          continue;

        case '\r':
          current.value.append("\\r");
          curr_char = file.read_char();

          if (*curr_char != '\n') {
            current.type = lex::Token::Error;
            return false;
          }

        case '\n':
          current.value.append("\\n");
          curr_char = nullptr;
          break;
      }

      break;
    }

    return true;
  }

  // "\r?\n(Special)"
  TRule(funny) {
    current.start = current.end;

    if (is_special())
      return true;

    current.type = lex::Token::NewLine;

    switch (*curr_char) {
      default:
        current.type = lex::Token::Error;
        return false;

      case '\r':
        current.value.append("\\r");
        curr_char = file.read_char();

        if (*curr_char != '\n') {
          current.type = lex::Token::Error;
          return false;
        }

      case '\n':
        current.value.append("\\n");
        curr_char = nullptr;
        break;
    }

    return true;
  }

  // Whitespace(Funny|Whitespace)Comment?
  TRule(ignore) {
    if (is_whitespace())
      return true;

    if (is_funny())
      return true;

    if (is_comment())
      return true;

    return false;
  }

  // "\w+"
  TRule(name) {
    current.start = current.end;
    current.type = lex::Token::Name;

    if (isalpha(*curr_char) || *curr_char == '_') {
      check:
        for (step(); curr_char; step()) {
          if (isalnum(*curr_char) || *curr_char == '_')
            continue;
          
          break;
        }

        return true;
    } else if (current.value.length() == 1)
      if (isalpha(current.value[0]) || current.value[0] == '_')
        return true;

    error:
      current.type = lex::Token::Error;
      return false;
  }

  // (Funny|Number|Name|String)
  TRule(plain_token) {
    if (is_funny())
      return true;

    if (is_number())
     return true;

    if (is_string())
      return true;

    if (is_name())
      return true;

    return false;
  }

  // (Ignore|PlainToken)
  TRule(token) {
    if (is_plain_token())
      return true;

    if (is_ignore())
      return true;

    return false;
  }

/*
  // (Whitespace|Comment|Triple)
  TRule(pseudo_extras) {
    if (is_whitespace())
      return true;

    if (is_comment())
      return true;

    if (is_triple())
      return true;

    t->end = b;

    return false;
  }

  // Whitespace(PseudoExtras|Token)
  TRule(pseudo_token) {
    if (is_whitespace())
      return true;

    if (is_pseudo_extras())
      return true;

    if (is_token(t))
      return true;

    return false;
  }
*/
}