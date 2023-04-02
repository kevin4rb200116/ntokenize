#include "ntokenize/main.hh"
#include <memory>

using namespace ntokenize;

int main(int argc, char** argv, char** environ) {
  Tokenizer tokenize = Tokenizer(stdin);

  while (true) {
    tokenize.next();

    printf("%s: '%s'\n",
      lex::token_name[tokenize.current.type].c_str(),
      tokenize.current.value.c_str());

    if (tokenize.current.type == lex::Token::EndMarker)
      break;
  }

  return EXIT_SUCCESS;
}