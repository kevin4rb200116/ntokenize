#include "tokenize.hh"

namespace lex {
  TokenNameList token_name = {
    {0, "ENDMARKER"},
    {1, "NAME"},
    {2, "NUMBER"},
    {3, "STRING"},
    {4, "NEWLINE"},
    {5, "INDENT"},
    {6, "DEDENT"},
    {7, "LPAR"},
    {8, "RPAR"},
    {9, "LSQB"},
    {10, "RSQB"},
    {11, "COLON"},
    {12, "COMMA"},
    {13, "SEMI"},
    {14, "PLUS"},
    {15, "MINUS"},
    {16, "STAR"},
    {17, "SLASH"},
    {18, "VBAR"},
    {19, "AMPER"},
    {20, "LESS"},
    {21, "GREATER"},
    {22, "EQUAL"},
    {23, "DOT"},
    {24, "PERCENT"},
    {25, "LBRACE"},
    {26, "RBRACE"},
    {27, "EQEQUAL"},
    {28, "NOTEQUAL"},
    {29, "LESSEQUAL"},
    {30, "GREATEREQUAL"},
    {31, "TILDE"},
    {32, "CIRCUMFLEX"},
    {33, "LEFTSHIFT"},
    {34, "RIGHTSHIFT"},
    {35, "DOUBLESTAR"},
    {36, "PLUSEQUAL"},
    {37, "MINEQUAL"},
    {38, "STAREQUAL"},
    {39, "SLASHEQUAL"},
    {40, "PERCENTEQUAL"},
    {41, "AMPEREQUAL"},
    {42, "VBAREQUAL"},
    {43, "CIRCUMFLEXEQUAL"},
    {44, "LEFTSHIFTEQUAL"},
    {45, "RIGHTSHIFTEQUAL"},
    {46, "DOUBLESTAREQUAL"},
    {47, "DOUBLESLASH"},
    {48, "DOUBLESLASHEQUAL"},
    {49, "AT"},
    {50, "ATEQUAL"},
    {51, "RARROW"},
    {52, "ELLIPSIS"},
    {53, "COLONEQUAL"},
    {54, "OP"},
    {55, "AWAIT"},
    {56, "ASYNC"},
    {57, "TYPE_IGNORE"},
    {58, "TYPE_COMMENT"},
    {59, "SOFT_KEYWORD"},
    {60, "ERRORTOKEN"},
    {61, "COMMENT"},
    {62, "NL"},
    {63, "ENCODING"},
    {64, "N_TOKENS"},
    {256, "NT_OFFSET"},
  };

  OperatorList _operator = {
    {"LPAR", "("},
    {"RPAR", ")"},
    {"LSQB", "["},
    {"RSQB", "]"},
    {"COLON", ":"},
    {"COMMA", ","},
    {"SEMI", ";"},
    {"PLUS", "+"},
    {"MINUS", "-"},
    {"STAR", "*"},
    {"SLASH", "/"},
    {"VBAR", "|"},
    {"AMPER", "&"},
    {"LESS", "<"},
    {"GREATER", ">"},
    {"EQUAL", "="},
    {"DOT", "."},
    {"PERCENT", "%"},
    {"LBRACE", "{"},
    {"RBRACE", "}"},
    {"EQEQUAL", "=="},
    {"NOTEQUAL", "!="},
    {"LESSEQUAL", "<="},
    {"GREATEREQUAL", ">="},
    {"TILDE", "~"},
    {"CIRCUMFLEX", "^"},
    {"LEFTSHIFT", "<<"},
    {"RIGHTSHIFT", ">>"},
    {"DOUBLESTAR", "**"},
    {"PLUSEQUAL", "+="},
    {"MINEQUAL", "-="},
    {"STAREQUAL", "*="},
    {"SLASHEQUAL", "/="},
    {"PERCENTEQUAL", "%="},
    {"AMPEREQUAL", "&="},
    {"VBAREQUAL", "|="},
    {"CIRCUMFLEXEQUAL", "^="},
    {"LEFTSHIFTEQUAL", "<<="},
    {"RIGHTSHIFTEQUAL", ">>="},
    {"DOUBLESTAREQUAL", "**="},
    {"DOUBLESLASH", "//"},
    {"DOUBLESLASHEQUAL", "//="},
    {"AT", "@"},
    {"ATEQUAL", "@="},
    {"RARROW", "->"},
    {"ELLIPSIS", "..."},
    {"COLONEQUAL", ":="},
  };

  TokenList token = {
    {"ENDMARKER", 0},
    {"NAME", 1},
    {"NUMBER", 2},
    {"STRING", 3},
    {"NEWLINE", 4},
    {"INDENT", 5},
    {"DEDENT", 6},
    {"LPAR", 7},
    {"RPAR", 8},
    {"LSQB", 9},
    {"RSQB", 10},
    {"COLON", 11},
    {"COMMA", 12},
    {"SEMI", 13},
    {"PLUS", 14},
    {"MINUS", 15},
    {"STAR", 16},
    {"SLASH", 17},
    {"VBAR", 18},
    {"AMPER", 19},
    {"LESS", 20},
    {"GREATER", 21},
    {"EQUAL", 22},
    {"DOT", 23},
    {"PERCENT", 24},
    {"LBRACE", 25},
    {"RBRACE", 26},
    {"EQEQUAL", 27},
    {"NOTEQUAL", 28},
    {"LESSEQUAL", 29},
    {"GREATEREQUAL", 30},
    {"TILDE", 31},
    {"CIRCUMFLEX", 32},
    {"LEFTSHIFT", 33},
    {"RIGHTSHIFT", 34},
    {"DOUBLESTAR", 35},
    {"PLUSEQUAL", 36},
    {"MINEQUAL", 37},
    {"STAREQUAL", 38},
    {"SLASHEQUAL", 39},
    {"PERCENTEQUAL", 40},
    {"AMPEREQUAL", 41},
    {"VBAREQUAL", 42},
    {"CIRCUMFLEXEQUAL", 43},
    {"LEFTSHIFTEQUAL", 44},
    {"RIGHTSHIFTEQUAL", 45},
    {"DOUBLESTAREQUAL", 46},
    {"DOUBLESLASH", 47},
    {"DOUBLESLASHEQUAL", 48},
    {"AT", 49},
    {"ATEQUAL", 50},
    {"RARROW", 51},
    {"ELLIPSIS", 52},
    {"COLONEQUAL", 53},
    {"OP", 54},
    {"AWAIT", 55},
    {"ASYNC", 56},
    {"TYPE_IGNORE", 57},
    {"TYPE_COMMENT", 58},
    {"SOFT_KEYWORD", 59},
    {"ERRORTOKEN", 60},
    {"COMMENT", 61},
    {"NL", 62},
    {"ENCODING", 63},
    {"N_TOKENS", 64},
    {"NT_OFFSET", 256},
  };

  TokenList EXACT_TOKEN_TYPE = {
    {"!=", 28},
    {"%", 24},
    {"%=", 40},
    {"&", 19},
    {"&=", 41},
    {"(", 7},
    {")", 8},
    {"*", 16},
    {"**", 35},
    {"**=", 46},
    {"*=", 38},
    {"+", 14},
    {"+=", 36},
    {",", 12},
    {"-", 15},
    {"-=", 37},
    {"->", 51},
    {".", 23},
    {"...", 52},
    {"/", 17},
    {"//", 47},
    {"//=", 48},
    {"/=", 39},
    {":", 11},
    {":=", 53},
    {";", 13},
    {"<", 20},
    {"<<", 33},
    {"<<=", 44},
    {"<=", 29},
    {"=", 22},
    {"==", 27},
    {">", 21},
    {">=", 30},
    {">>", 34},
    {">>=", 45},
    {"@", 49},
    {"@=", 50},
    {"[", 9},
    {"]", 10},
    {"^", 32},
    {"^=", 43},
    {"{", 25},
    {"|", 18},
    {"|=", 42},
    {"}", 26},
    {"~", 31},
  };
}

namespace tokenize {
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

  void TokenInfo::dump(bool with_data) {
    string format;

    if (with_data)
      format =
        "%s { type: %i, "
        "raw_value: \"%s\", "
        "start: %i, "
        "end: %i, "
        "data: \"%s\" }\n";
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
      data.c_str()
    );
  }

  TokenInfo::TokenInfo(int type, string raw_value, int start, int end, string data)
      :type(type), raw_value(raw_value), start(start), end(end), data(data) {}

  TokenInfo::TokenInfo() {
    type=0;
    raw_value=string();
    start=0;
    end=0;
    data=string();
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

  // "[ \f\t]*"
  bool Whitespace(TokenInfo* t) {
    int b=t->end;
    t->start = t->end;

    t->type = lex::token["TYPE_IGNORE"];

    switch (t->data[t->end]) {
      case ' ':
      case '\f':
      case '\t':
        t->end++;
        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    for (t->end; t->end <= t->data.length(); t->end++) {
      switch (t->data[t->end]) {
        case ' ':
        case '\f':
        case '\t':
          continue;

        default:
          break;
      }

      break;
    }

    t->start = b;
    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // "#[^\r\n]*"
  bool Comment(TokenInfo* t) {
    int b=t->end;
    t->start = t->end;
    t->type = lex::token["COMMENT"];

    if (t->data[t->end] != '#') {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    for (t->end; t->end <= t->data.length(); t->end++) {
      switch (t->data[t->end]) {
        case '\r':
        case '\n':
          break;

        default:
          continue;
      }

      break;
    }

    switch (t->data[t->end]) {
      case '\r':
      case '\n':
        t->end++;
        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    //t->end = t->data.length();

    t->start = b;
    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    t->type = lex::token["COMMENT"];

    return true;
  }

  // Whitespace(Funny|Whitespace)Comment?
  bool Ignore(TokenInfo* t) {
    int end = t->end;

    if (Whitespace(t))
      return true;

    t->end = end;

    if (Funny(t))
      return true;

    t->end = end;

    if (Comment(t))
      return true;

    t->end = end;

    return false;
  }

  // "\w+"
  bool Name(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NAME"];

    if (!isalpha(t->data[t->end])) {
      if (t->data[t->end] != '_') {
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
      }
    }

    t->end++;

    for (t->end; t->end <= t->data.length(); t->end++) {
      if (isalnum(t->data[t->end]))
        continue;

      if (t->data[t->end] == '_')
        continue;

      break;
    }

    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    if (t->raw_value.length() == 0) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // "0[xX](?:_?[0-9a-fA-F])+"
  bool HexNumber(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    switch (t->data[t->end]) {
      case '0':
        t->end++;

        switch (t->data[t->end]) {
          case 'x':
          case 'X':
            t->end += 2;
            break;

          default:
            t->type = lex::token["ERRORTOKEN"];
            t->end = b;
            return false;
        }

        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    for (t->end; t->data.length() > t->end; t->end++) {
      if (t->data[t->end] >= '0')
        if (t->data[t->end] <= '9')
          continue;

      if (t->data[t->end] >= 'a')
        if (t->data[t->end] <= 'f')
          continue;

      if (t->data[t->end] >= 'A')
        if (t->data[t->end] <= 'F')
          continue;

      break;
    }

    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    if (t->raw_value.length() < 3) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // "0[bB](?:_?[01])+"
  bool Binnumber(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    switch (t->data[t->end]) {
      case '0':
        t->end++;

        switch (t->data[t->end]) {
          case 'b':
          case 'B':
            t->end += 2;
            break;

          default:
            t->type = lex::token["ERRORTOKEN"];
            t->end = b;
            return false;
        }

        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    for (t->end; t->data.length() > t->end; t->end++) {
      if (t->data[t->end] == '0')
        continue;

      if (t->data[t->end] == '1')
        continue;

      break;
    }

    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    if (t->raw_value.length() < 3) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // "0[oO](?:_?[0-7])+"
  bool Octnumber(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    switch (t->data[t->end]) {
      case '0':
        t->end++;

        switch (t->data[t->end]) {
          case 'o':
          case 'O':
            t->end += 2;
            break;

          default:
            t->type = lex::token["ERRORTOKEN"];
            t->end = b;
            return false;
        }

        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    for (t->end; t->data.length() > t->end; t->end++) {
      if (t->data[t->end] >= '0')
        if (t->data[t->end] <= '7')
          continue;

      break;
    }

    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    if (t->raw_value.length() < 3) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // "(?:0(?:_?0)*|[1-9](?:_?[0-9])*)"
  bool Decnumber(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    if (!(t->data[t->end] >= '0')) {
      if (!(t->data[t->end] <= '9')) {
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
      }
    }

    for (t->end; t->data.length() > t->end; t->end++) {
      if (t->data[t->end] >= '0')
        if (t->data[t->end] <= '9')
          continue;

      break;
    }

    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    if (t->raw_value.length() == 0) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // "(HexNumber|Binnumber|Octnumber|Decnumber)"
  bool Intnumber(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    if (HexNumber(t)) {
      return true;
    }

    t->end = b;

    if (Binnumber(t)) {
      return true;
    }

    t->end = b;

    if (Octnumber(t)) {
      return true;
    }

    t->end = b;

    if (Decnumber(t)) {
      return true;
    }

    t->end = b;

    return false;
  }

  // "[eE][-+]?[0-9](?:_?[0-9])*"
  bool Exponent(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    switch (t->data[t->end]) {
      case 'e':
      case 'E':
        t->end++;

        switch (t->data[t->end]) {
          case '-':
          case '+':
            t->end++;
            break;
        }

        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    if (!Decnumber(t)) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    t->end++;
    t->start = b;

    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // ("Decnumber\.Decnumber)?'|r'\.Decnumber)Exponent?
  bool Pointfloat(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    if (Decnumber(t)) {
      t->end++;
    }

    if (t->data[t->end] != '.') {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    t->end++;

    if (!Decnumber(t)) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    t->end++;

    if (Exponent(t))
      t->end++;

    t->type = lex::token["NUMBER"];
    t->start=b;

    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // "Decnumber+(_Decnumber+)*Exponent"
  bool Expfloat(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    if (!Decnumber(t)) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    t->end++;

    if (!Exponent(t)) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    t->end++;
    t->start=b;

    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // (Pointfloat|Expfloat);
  bool Floatnumber(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    if (Pointfloat(t))
      return true;

    t->end = b;

    if (Expfloat(t))
      return true;

    t->end = b;

    return false;
  }

  // "([0-9](?:_?[0-9])*[jJ]|(Floatnumber[jJ])"
  bool Imagnumber(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    if (!Floatnumber(t)) {
      t->type = lex::token["NUMBER"];
      t->end = b;

      if (!Decnumber(t)) {
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
      }
    }

    t->end++;

    switch (t->data[t->end]) {
      case 'j':
      case 'J':
        t->end++;
        break;
      
      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    t->start = b;
    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // (Imagnumber|Floatnumber|Intnumber)
  bool Number(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["NUMBER"];

    if (Floatnumber(t))
      return true;

    t->end = b;

    if (Imagnumber(t))
      return true;

    t->end = b;

    if (Intnumber(t))
      return true;

    t->end = b;

    return false;
  }

  // (|RB|u|Rb|Br|b|fr|r|Rf|br|fR|Fr|R|f|rb|FR|BR|rf|bR|rB|B|F|rF|RF|U)
  bool StringPrefix(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    switch (t->data[t->end]) {
      case 'u':
      case 'U':
        break;

      case 'b':
      case 'B':
        t->end++;

        switch (t->data[t->end]) {
          case 'r':
          case 'R':
            t->end++;
            break;
          
          default:
            break;
        }

        break;

      case 'f':
      case 'F':
        t->end++;

        switch (t->data[t->end]) {
          case 'r':
          case 'R':
            t->end++;
            break;
          
          default:
            break;
        }

        break;

      case 'r':
      case 'R':
        t->end++;

        switch (t->data[t->end]) {
          case 'b':
          case 'B':
            t->end++;
            break;

          case 'f':
          case 'F':
            t->end++;
            break;
          
          default:
            break;
        }

        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    t->end = b;

    if (!Name(t)) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    if (t->raw_value.length() > 2) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // "[^'\\]*(?:\\.[^'\\]*)*'"
  bool Single(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    t->type = lex::token["STRING"];

    switch (t->data[t->end]) {
      case '\'':
        t->end++;
        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    for (t->end; t->data.length() > t->end; t->end++) {
      if (t->data[t->end] == '\\')
        t->end += 2;

      if (t->data[t->end] == '\'')
        break;
    }

    switch (t->data[t->end]) {
      case '\'':
        t->end++;
        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    t->start = b;
    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // "[^\"\\]*(?:\\.[^\"\\]*)*\"\""
  bool Double(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    t->type = lex::token["STRING"];

    switch (t->data[t->end]) {
      case '"':
        t->end++;
        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    for (t->end; t->data.length() > t->end; t->end++) {
      if (t->data[t->end] == '\\')
        t->end += 2;

      if (t->data[t->end] == '"')
        break;
    }

    switch (t->data[t->end]) {
      case '"':
        t->end++;
        break;

      default:
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
    }

    t->start = b;
    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // "[^'\\]*(?:(?:\\.|'(?!''))[^'\\]*)*'''"
  bool Single3(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    t->type = lex::token["STRING"];

    if (t->data[t->end] != '\'') {
      if (t->data[t->end+1] != '\'') {
        if (t->data[t->end+2] != '\'') {
          t->type = lex::token["ERRORTOKEN"];
          t->end = b;
          return false;
        }
      }
    }

    t->end += 3;

    for (t->end; t->data.length() > t->end; t->end++) {
      if (t->data[t->end] == '\\')
        t->end += 2;

      if (t->data[t->end] == '\'')
        if (t->data[t->end+1] == '\'')
          if (t->data[t->end+2] == '\'')
            break;
    }

    if (t->data[t->end] != '\'') {
      if (t->data[t->end+1] != '\'') {
        if (t->data[t->end+2] != '\'') {
          t->type = lex::token["ERRORTOKEN"];
          t->end = b;
          return false;
        }
      }
    }

    t->end += 3;

    t->start = b;
    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    if (t->raw_value.length() < 6) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // "[^\"\\]*(?:(?:\\.|\"(?!\"\"))[^\"\\]*)*\"\"\""
  bool Double3(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    t->type = lex::token["STRING"];

    if (t->data[t->end] != '"') {
      if (t->data[t->end+1] != '"') {
        if (t->data[t->end+2] != '"') {
          t->type = lex::token["ERRORTOKEN"];
          t->end = b;
          return false;
        }
      }
    }

    t->end += 3;

    for (t->end; t->data.length() > t->end; t->end++) {
      if (t->data[t->end] == '\\')
        t->end += 2;

      if (t->data[t->end] == '"')
        if (t->data[t->end+1] == '"')
          if (t->data[t->end+2] == '"')
            break;
    }

    if (t->data[t->end] != '"') {
      if (t->data[t->end+1] != '"') {
        if (t->data[t->end+2] != '"') {
          t->type = lex::token["ERRORTOKEN"];
          t->end = b;
          return false;
        }
      }
    }

    t->end += 3;

    t->start = b;
    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    if (t->raw_value.length() < 6) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    return true;
  }

  // (StringPrefix\'\'\'|StringPrefix\"\"\")
  bool Triple(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    if (StringPrefix(t))
      t->end++;

    if (Single3(t)) {
      t->end++;
      t->start = b;
      t->raw_value = t->data.substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Double3(t)) {
      t->end++;
      t->start = b;
      t->raw_value = t->data.substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    return false;
  }

  // '(StringPrefix*(Single|Double)
  bool String(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["STRING"];

    if (StringPrefix(t))
      t->end++;

    if (Single(t)) {
      t->end++;

      t->start = b;
      t->raw_value = t->data.substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    if (Double(t)) {
      t->end++;

      t->start = b;
      t->raw_value = t->data.substr(t->start,t->end-t->start);
      t->end--;

      return true;
    }

    return false;
  }

  // "StringPrefix*(Triple|String)"
  bool ContStr(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    if (StringPrefix(t))
      t->end++;

    if (!Triple(t)) {
      if (!String(t)) {
        t->type = lex::token["ERRORTOKEN"];
        t->end = b;
        return false;
      }
    }

    t->end++;

    t->start = b;
    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // '\\~|\\}|\\|=|\\||\\{|\\^=|\\^|\\]|\\[|@=|@|>>=|>>|>=|>|==|=|<=|<<=|<<|<|;|:=|:|/=|//=|//|/|\\.\\.\\.|\\.|\\->|\\-=|\\-|,|\\+=|\\+|\\*=|\\*\\*=|\\*\\*|\\*|\\)|\\(|\\&=|\\&|%=|%|!=)'
  bool Special(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;
    t->type = lex::token["OP"];

    for (int i=3; i >= 0; i--) {
      for (auto _operator : lex::_operator) {
        if (_operator.second == t->data.substr(t->end,i)) {
          t->raw_value = t->data.substr(b,i);
          t->end = (b+i)-1;

          return true;
        }
      }
    }

    t->type = lex::token["ERRORTOKEN"];
    t->end = b;

    return false;
  }

  // "\r?\n(Special)"
  bool Funny(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    if (Special(t))
      return true;

    t->end = b;

    t->type = lex::token["NEWLINE"];

    if (t->data[t->end] == '\r')
      t->end++;

    if (!(t->data[t->end] == '\n')) {
      t->type = lex::token["ERRORTOKEN"];
      t->end = b;
      return false;
    }

    t->end++;
    t->raw_value = t->data.substr(t->start,t->end-t->start);
    t->end--;

    return true;
  }

  // (Funny|Number|Name|ContStr)
  bool PlainToken(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    if (Number(t))
      return true;

    t->end = b;

    if (Funny(t))
      return true;

    t->end = b;

    if (String(t))
      return true;

    t->end = b;

    if (Name(t))
      return true;

    t->end = b;

    return false;
  }

  // (Ignore|PlainToken)
  bool Token(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    if (Ignore(t))
      return true;

    t->end = b;

    if (PlainToken(t))
      return true;

    t->end = b;

    return false;
  }

  // (Whitespace|Comment|Triple)
  bool PseudoExtras(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    if (Whitespace(t))
      return true;

    t->end = b;

    if (Comment(t))
      return true;

    t->end = b;

    if (Triple(t))
      return true;

    t->end = b;

    return false;
  }

  // Whitespace(PseudoExtras|Token)
  bool PseudoToken(TokenInfo* t) {
    int b = t->end;
    t->start = t->end;

    if (Whitespace(t))
      return true;

    t->end = b;

    if (PseudoExtras(t))
      return true;

    t->end = b;

    if (Token(t))
      return true;

    t->end = b;

    return false;
  }

  vector<TokenInfo> File(FILE* fp) {
    vector<TokenInfo> file_tokens;
    TokenInfo t = TokenInfo();

    if (feof(fp)) {
      file_tokens.push_back(t);
      return file_tokens;
    }

    t.data = tokenize::read_file(stdin);

    for (t.end=0; t.data.length() > t.end; t.end++) {
      tokenize::PseudoToken(&t);

      file_tokens.push_back(t);
    }

    t.type=lex::token["ENDMARKER"];
    t.raw_value.clear();
    t.start++;
    t.end++;
    file_tokens.push_back(t);

    return file_tokens;
  }
}
