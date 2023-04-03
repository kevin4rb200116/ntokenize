#include "ntokenize/main.hh"

namespace ntokenize {
  // "[ \f\t]*"
  bool Tokenizer::is_whitespace() {
    while (check({'\f',lex::Token::Ignore}, {'\t',lex::Token::Ignore})
           || check({' ',lex::Token::Ignore}));

    if (current.value.raw.length() == 0)
      return false;

    current.type = lex::Token::Ignore;
    return true;
  }

  // "#[^\r\n]*"
  bool Tokenizer::is_comment() {
    if (!check({'#', lex::Token::Comment})) {
      current.type = lex::Token::Error;
      return false;
    }

    while (curr_char) {
      if (check({'\r',lex::Token::NewLine})) {
        if (check({'\n',lex::Token::NewLine}))
          break;

        return false;
      }

      step();
    }

    current.type = lex::Token::Comment;
    return true;
  }

  // "\r?\n(Special)"
  bool Tokenizer::is_funny() {
    if (is_special())
      return true;

    if (check({'\r',lex::Token::NewLine})) {
      if (check({'\n',lex::Token::NewLine}))
        return true;
      
      return false;
    } if (check({'\n',lex::Token::NewLine}))
      return true;

    return false;
  }

  // "\w+"
  bool Tokenizer::is_name() {
    auto is_alpha = [](char x) { return (bool) isalpha(x); };
    auto is_alnum = [](char x) { return (bool) isalnum(x); };

    if (check(is_alpha, lex::Token::Name)
        || check({'_', lex::Token::Name})) {
      while (check(is_alnum, lex::Token::Name)
             || check({'_', lex::Token::Name}));
      
      if (current.value.raw.length() == 0)
        return false;

      current.type = lex::Token::Name;
      return true;
    }

    current.type = lex::Token::Error;
    return false;
  }

  // Whitespace|Comment?
  bool Tokenizer::is_ignore() {
    return is_whitespace() || is_comment();
  }

  // (Funny|Number|Name|String)
  bool Tokenizer::is_plain_token() {
    return is_funny() || is_number() || is_string() || is_name();
  }

  // (Ignore|PlainToken)
  bool Tokenizer::is_token() {
    return is_plain_token() || is_ignore();
  }
}