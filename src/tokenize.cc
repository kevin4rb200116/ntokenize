#include "ntokenize/tokenize.hh"

namespace ntokenize {
  int TokenInfo::exact_type() {
    bool have_op=false;

    for (auto &&type: lex::EXACT_TOKEN_TYPE)
      if (raw_value == type.first)
        have_op=true;

    if (type == lex::token["OP"] && have_op)
      return lex::EXACT_TOKEN_TYPE[raw_value];
    else
      return type;
  }

  void TokenInfo::dump(bool with_line) {
    string format;

    if (with_line)
      format =
        "%s { type: %i, "
        "raw_value: \"%s\", "
        "start: %i, "
        "end: %i, "
        "line: \"%s\" }\n";
    else
      format =
        "%s { type: %i, "
        "raw_value: \"%s\", "
        "start: %i, "
        "end: %i }\n";

    printf(format.c_str(),
      lex::token_name[exact_type()].c_str(),
      type,
      raw_value.c_str(),
      start,
      end,
      line->c_str()
    );
  }

  void TokenInfo::from(TokenInfo* t) {
    type = t->type;

    raw_value.clear();
    raw_value.append(t->raw_value);

    start = t->start;
    end = t->end;

    line = t->line;
  }

  string read_file(FILE* fp) {
    string file;

    if (feof(fp))
      return file;

    for (char c=getc(fp); !feof(fp); c=getc(fp))
      file.push_back(c);

    return file;
  }

  string read_line(FILE* fp) {
    string line;

    if (feof(fp)) {
      return line;
    }

    for (char c=getc(fp); !feof(fp); c=getc(fp)) {
      line.push_back(c);

      if (c == '\n')
        break;
    }

    return line;
  }

  TokenInfo* Tokenizer::next() {
    if (current.end != 0)
      current.end++;

    if (current.end == current.line->length()) {
      current.type = 0;
      current.raw_value.clear();
      current.start = 0;
      current.end = 0;
      current.line->clear();
    }

    if (current.line->empty()) {
      current.line->clear();
      current.line->append(read_line(fp));

      if (current.line->empty()) {
        current.type = lex::token["ENDMARKER"];

        current.dump(false);

        return &current;
      }
    }

    PseudoToken(&current);

    last.from(&current);

    if (current.end == 0)
      current.end++;

    return &last;
  }
}
