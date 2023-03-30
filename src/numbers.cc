#include "ntokenize/tokenize.hh"

namespace ntokenize {
  // "dec_number = (?:0(?:_?0)*|[1-9](?:_?[0-9])*)"
  inline bool Tokenizer::is_dec_number() {
    current.start = current.end;

    if (isalnum(*curr_char)) {
      if (!isdigit(*curr_char))
        goto error;

      for (step(); curr_char; step()) {
        if (isalnum(*curr_char))
          if (isdigit(*curr_char))
            continue;

        break;
      }

      current.type = lex::Token::Number;
      return true;
    }

    error:
      current.type = lex::Token::Error;
      return false;
  }

  // bin_number = "0[bB](?:_?[01])+"
  inline bool Tokenizer::is_bin_number() {
    if (isalnum(*curr_char)) {
      for (step(); curr_char; step()) {
        if (isalnum(*curr_char)) {
          if ('0' == *curr_char || *curr_char == '1')
            continue;
          else
            break;
        }

        break;
      }

      if (current.value.length() < 3)
        goto error;

      return true;
    }

    error:
      return false;
  }

  // oct_number = "0[oO](?:_?[0-7])+"
  inline bool Tokenizer::is_oct_number() {
    if (isalnum(*curr_char)) {
      for (step(); curr_char; step()) {
        if (isalnum(*curr_char)) {
          if ('0' <= *curr_char && *curr_char <= '7')
            continue;
          else
            break;
        }

        break;
      }

      if (current.value.length() < 3)
        goto error;

      return true;
    }

    error:
      return false;
  }

  // hex_number = "0[xX](?:_?[0-9a-fA-F])+"
  inline bool Tokenizer::is_hex_number() {
    if (isalnum(*curr_char)) {
      for (step(); curr_char; step()) {
        if (isalnum(*curr_char)) {
          if (isdigit(*curr_char))
            continue;
          else if ('a' <= *curr_char && *curr_char <= 'f')
            continue;
          else if ('A' <= *curr_char && *curr_char <= 'F')
            continue;
          else
            break;
        }

        break;
      }

      if (current.value.length() < 3)
        goto error;

      return true;
    }

    error:
      return false;
  }

  // exponent = "[eE][-+]?Decnumber(?:_?Decnumber)*"
  bool Tokenizer::is_exponent() {
    if (isalnum(*curr_char)) {
      if ('-' == *curr_char || *curr_char == '+')
        step();

      if (!is_dec_number())
        goto error;

      return true;
    }

    error:
      return false;
  }

  // point_float = (Decnumber\.Decnumber)?|\.Decnumber)Exponent?
  bool Tokenizer::is_point_float() {
    if (!is_dec_number())
      goto error;

    switch (*curr_char) {
      case 'e':
      case 'E':
        step();
        if (!is_exponent())
          if (!isdigit(current.value[current.value.length()-1]))
            goto error;

      default:
        break;
    }

    current.type = lex::Token::Number;
    return true;

    error:
      current.type = lex::Token::Error;
      return false;
  }

  // number = (imag_number|float_number|int_number)
  bool Tokenizer::is_number() {
    if (is_dec_number()) {
      switch (*curr_char) {
        case 'j':
        case 'J':
          step();

          current.type = lex::Token::Number;
          return true; // imag_number = "(Decnumber(?:_?Decnumber)*[jJ]|(Floatnumber[jJ])"

        case 'e':
        case 'E':
          step();
          if (!is_exponent())
            goto error;

          current.type = lex::Token::Number;
          return true; // "Decnumber+(_Decnumber+)*Exponent"
        
        case '.':
          step();
          if (!is_point_float())
            goto error;

          current.type = lex::Token::Number;
          return true; // (Decnumber\.Decnumber)?|\.Decnumber)Exponent?

        case 'b':
        case 'B':
          if (current.value[current.value.length()-1] != '0')
            goto error;

          step();

          if (!is_bin_number())
            goto error;

          current.type = lex::Token::Number;
          return true;

        case 'o':
        case 'O':
          if (current.value[current.value.length()-1] != '0')
            goto error;

          step();

          if (!is_oct_number())
            goto error;

          current.type = lex::Token::Number;
          return true;

        case 'x':
        case 'X':
          if (current.value[current.value.length()-1] != '0')
            goto error;

          step();

          if (!is_hex_number())
            goto error;

          current.type = lex::Token::Number;
          return true;

        default:
          break;
      }

      if (!isdigit(current.value[current.value.length()-1]))
        return false;

      current.type = lex::Token::Number;
      return true;
    }

    error:
      current.type = lex::Token::Error;
      return false;
  }
}