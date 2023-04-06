#include "ntokenize/main.hh"
#include <memory>

using namespace ntokenize;

int main(int argc, char** argv, char** environ) {
  Tokenizer tokenize = Tokenizer(stdin);

  while (true) {
    tokenize.next();

    if (tokenize.current.type == lex::Token::NewLine) {
      printf("\n");
      continue;
    }

    if (tokenize.current.type != lex::Token::Ignore)
      printf("'%s' ", tokenize.current.value.raw.c_str());

    if (tokenize.current.type == lex::Token::EndMarker)
      break;
  }

  return EXIT_SUCCESS;
}