#include "ntokenize/main.hh"

namespace ntokenize {
  unique_ptr<char> File::read_char() {
    if (feof(fp))
      return nullptr;

    return make_unique<char>(getc(fp));
  }

  Token::Token() {
    type = lex::Token::Error;
    start = pair<size_t,size_t>();
    end = pair<size_t,size_t>();
    value=string();
  }

  Token::Token(lex::Token type,
              string value,
              pair<size_t,size_t> start, pair<size_t,size_t> end) {
    type=type;
    value=value;
    start=start;
    end=end;
  }

  void Token::clear() {
    type = lex::Token::Error;
    start = pair<size_t,size_t>();
    end = pair<size_t,size_t>();
    value.clear();
  }

  void Token::copy(Token* other) {
    clear();

    type = other->type;
    start = pair<size_t,size_t>(other->start);
    end = pair<size_t,size_t>(other->end);
    value.append(other->value);
  }


  void Tokenizer::eat() {
    current.value.push_back(*curr_char);
    current.end.second++;
    current.abs_end++;
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
    current.clear();

    if (last.type == lex::Token::NewLine) {
      current.start.first++;
      current.start.second = 0;
      current.end.first++;
      current.end.second = 0;
    }

    if (curr_char == nullptr) {
      curr_char = file.read_char();

      if (curr_char == nullptr) null_char: {
        current.type = lex::Token::EndMarker;

        current.start.first++;
        current.start.second = 0;

        current.end.first++;
        current.end.second = 0;

        return;
      }
    }

    current.abs_start = current.abs_end;
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