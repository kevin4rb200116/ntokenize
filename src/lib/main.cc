#include "ntokenize/main.hh"

namespace ntokenize {
  unique_ptr<char> File::read_char() {
    if (feof(fp))
      return nullptr;

    return make_unique<char>(getc(fp));
  }

  void Tokenizer::eat() {
    current.value.raw.push_back(*curr_char);
    current.pos.rel.end.y++;
    current.pos.abs.end++;
  }

  void Tokenizer::step() {
    eat();
    curr_char = file.read_char();
  }

  bool Tokenizer::check(pair<char,lex::Token> x, pair<char,lex::Token> y) {
    pair<bool,lex::Token> r = compare(*curr_char, x, y);
    current.type = r.second;

    if (r.first)
      step();

    return r.first;
  }

  bool Tokenizer::check(pair<char,lex::Token> x) {
    auto r = compare(*curr_char, x);
    current.type = r.second;

    if (r.first)
      step();

    return r.first;
  }

  bool Tokenizer::check(char a, char b, lex::Token T) {
    if (a <= *curr_char && *curr_char <= b) {
      current.type = T;
      step();
      return true;
    }

    current.type = lex::Token::Error;
    return false;
  }

  bool Tokenizer::check(bool (*test)(char), lex::Token T) {
    if (test(*curr_char)) {
      current.type = T;
      step();
      return true;
    }

    current.type = lex::Token::Error;
    return false;
  }

  void Tokenizer::next() {
    if (!curr_char) {
      curr_char = file.read_char();

      if (!curr_char) null_char: {
        current.type = lex::Token::EndMarker;
        current.pos.rel.start = {current.pos.rel.start.x+1, 0};
        current.pos.rel.end = current.pos.rel.start;

        return;
      }
    }

    current.value.clear();

    if (current.type == lex::Token::NewLine) {
      current.clear();

      current.pos.rel.start = {last.pos.rel.start.x+1, 0};
      current.pos.rel.end = {last.pos.rel.start.x+1, 0};
    }

    current.pos.abs.start = last.pos.abs.end;
    current.pos.rel.start = last.pos.rel.end;

    if (is_token()) {
      last.copy(&current);
      return;
    }

    curr_char = file.read_char();
    if (curr_char == nullptr)
      goto null_char;
  }

  inline pair<bool,lex::Token>
  compare(char x, pair<char,lex::Token> a, pair<char,lex::Token> b) {
    if (x == a.first)
      return {true, a.second};

    else if (x == b.first)
      return {true, b.second};

    return {false, lex::Token::Error};
  }

  inline pair<bool,lex::Token>
  compare(char x, pair<char,lex::Token> y) {
    if (x == y.first)
      return {true, y.second};

    return {false,lex::Token::Error};
  }
} // namespace ntokenize