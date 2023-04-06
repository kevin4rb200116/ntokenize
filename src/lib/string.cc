#include "ntokenize/main.hh"

namespace ntokenize {
  // (|RB|u|Rb|Br|b|fr|r|Rf|br|fR|Fr|R|f|rb|FR|BR|rf|bR|rB|B|F|rF|RF|U)
  bool Tokenizer::is_string_prefix() {
    if (check({'u',lex::Token::Name},{'U',lex::Token::Name}))
      return true;
    
    if (check({'b',lex::Token::Name},{'B',lex::Token::Name})) {
      if (check({'r',lex::Token::Name},{'R',lex::Token::Name}));
      else current.type = lex::Token::Name;

      return true;
    }

    if (check({'f',lex::Token::Name},{'F',lex::Token::Name})) {
      if (check({'r',lex::Token::Name},{'R',lex::Token::Name}));
      else current.type = lex::Token::Name;

      return true;
    }

    if (check({'r',lex::Token::Name},{'R',lex::Token::Name})) {
      if (check({'b',lex::Token::Name},{'B',lex::Token::Name})
          || check({'f',lex::Token::Name},{'F',lex::Token::Name}));
      else current.type = lex::Token::Name;

      return true;
    }

    current.type = lex::Token::Error;
    return false;
  }

  // '(StringPrefix*(Single|Double)
  bool Tokenizer::is_string() {
    bool with_prefix = false;

    if (is_string_prefix())
      with_prefix = true;

    struct { char c; lex::Token t; } strf = {0x00,lex::Token::Error};

    if (check({'\'',lex::Token::SingleString},{'"',lex::Token::DoubleString})) {
      if (current.type == lex::Token::SingleString)
        strf = {'\'',lex::Token::SingleString};
      else if (current.type == lex::Token::DoubleString)
        strf = {'"',lex::Token::DoubleString};

      if (check({strf.c,strf.t})) {
        // """
        // a special string to prevent explicit escaping
        // """
        if (check({strf.c,strf.t})) {
          if (current.type == lex::Token::SingleString)
            strf = {'\'',lex::Token::Single3String};
          else if (current.type == lex::Token::DoubleString)
            strf = {'"',lex::Token::Double3String};

          while (true) {
            if (!curr_char)
              return false;

            if (check({'\\', lex::Token::Ignore}))
              step();

            if (check({strf.c,strf.t}))
              if (check({strf.c,strf.t}))
                if (check({strf.c,strf.t}))
                  break;
            
            step();
          }

          current.type = strf.t;

          return true;
        } else current.type = strf.t;

        return true;
      }


      /* x = "simple string"

         y = "\
         a simple string with explicit escapes\
         " */
      while (true) {
        if (!curr_char)
          return false;

        if (check({'\\', lex::Token::Ignore})) // escape
          step(); // eat character

        if (check({'\n', lex::Token::NewLine})) { // error multi-line string without escape newline
          current.type = lex::Token::Error;
          return false;
        }

        if (check({strf.c,strf.t}))
          break;

        step();
      }

      current.type = strf.t;

      return true;
    }

    if (with_prefix) {
      /*
      even though we don't have a string, we do have
      its prefix, which means we have a name.
      */

      return is_name();
    }

    return false;
  }
} // namespace tokenize