#include "ntokenize/tokenize.hh"
#include <memory>

using namespace ntokenize;

int main(int argc, char** argv, char** environ) {
  Tokenizer tokenize = Tokenizer(stdin);

  while (!feof(stdin)) {
    tokenize.next();

    if (tokenize.current.type == lex::Token::EndMarker)
      break;

    printf("%s\n", tokenize.current.as_string().c_str());
  }

  printf("%s\n", tokenize.current.as_string().c_str());

  return EXIT_SUCCESS;
}
