#include "ntokenize/main.hh"

namespace ntokenize {
  // number = (imag_number|float_number|int_number)
  bool Tokenizer::is_number() {
    if (isalnum(*curr_char)) {
      if (isdigit(*curr_char)) {
        if (check({'0',lex::Token::DecNumber})) {
          if (check({'B',lex::Token::Error},{'b',lex::Token::Error})) {
            while (check({'0',lex::Token::BinNumber},{'1',lex::Token::BinNumber}));
            current.type = lex::Token::BinNumber;

            return true;

          } else if (check({'O',lex::Token::Error},{'o',lex::Token::Error})) {
            while (check('0','7',lex::Token::OctNumber));
            current.type = lex::Token::OctNumber;

            return true;

          } else if (check({'X',lex::Token::Error},{'x',lex::Token::Error})) {
            while (check('0','9',lex::Token::HexNumber)
                   || check('a','f',lex::Token::HexNumber)
                   || check('A','F',lex::Token::HexNumber));

            current.type = lex::Token::HexNumber;
            return true;
          }
        }

        if (check('0','9', (lex::Token) current.type)) {
          while (check('0','9',lex::Token::FloatNumber));
          current.type = lex::Token::DecNumber;
        }

        if (check({'.',lex::Token::Error})) {
          while (check('0','9',lex::Token::FloatNumber));
          current.type = lex::Token::FloatNumber;
        } else
          current.type = lex::Token::DecNumber;

        auto T = (lex::Token) current.type;

        if (check({'E',lex::Token::Error},{'e',lex::Token::Error})) {
          if (check({'-',lex::Token::Error},{'+',lex::Token::Error}));

          while (check('0','9', (lex::Token) current.type));
        }

        current.type = T;

        if (check({'J',lex::Token::ImagNumber},{'j',lex::Token::ImagNumber}))
          current.type = lex::Token::ImagNumber;
        else
          current.type = T;

        return true;
      }
    }

    current.type = lex::Token::Error;
    return false;
  }
}