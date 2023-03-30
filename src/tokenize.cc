#include "ntokenize/tokenize.hh"

namespace ntokenize {
  unique_ptr<char> File::read_char() {
    if (feof(fp))
      return nullptr;
    
    return make_unique<char>(getc(fp));
  }

  unique_ptr<string> File::read_file() {
    string file = string();

    if (feof(fp))
      return make_unique<string>(file);

    for (char c=getc(fp); !feof(fp); c=getc(fp))
      file.push_back(c);

    return make_unique<string>(file);
  }

  unique_ptr<string> File::read_line() {
    string line;

    if (feof(fp))
      return make_unique<string>(line);

    for (char c=getc(fp); !feof(fp); c=getc(fp)) {
      line.push_back(c);

      if (c == '\n')
        break;
    }

    return make_unique<string>(line);
  }

  Token::Token() {
    type = lex::Token::Error;
    start = pair<size_t,size_t>();
    end = pair<size_t,size_t>();
    value=string();
  }

  Token::Token(lex::Token type,
              string value, pair<size_t,size_t> start, pair<size_t,size_t> end) {
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

  unique_ptr<Token> Token::from(Token* other) {
    Token t;

    t.clear();

    t.type = other->type;
    t.start = pair<size_t,size_t>(other->start);
    t.end = pair<size_t,size_t>(other->end);
    t.value.append(other->value);

    return make_unique<Token>(t);
  }

  void Token::copy(Token* other) {
    clear();

    type = other->type;
    start = pair<size_t,size_t>(other->start);
    end = pair<size_t,size_t>(other->end);
    value.append(other->value);
  }

  string Token::as_string() {
    char* format = (char*)
      "Token "
      "{"
      " type: \"%s\","
      " start: { %i, %i },"
      " end: { %i, %i }"
      " value: \"%s\" "
      "}";
    
    string s=string();
    s.reserve(256);

    sprintf(&s[0], format,
      lex::token_name[type].c_str(),
      start.first,start.second,
      end.first,end.second,
      value.c_str()
    );

    return s;
  }

  void Tokenizer::eat() {
    current.value.push_back(*curr_char);
    current.end.second++;
  }

  void Tokenizer::step() {
    eat();
    curr_char = file.read_char();
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

    if (is_token()) {
      last.copy(&current);
      return;
    }

    curr_char = file.read_char();
    if (curr_char == nullptr)
      goto null_char;
  }
}
