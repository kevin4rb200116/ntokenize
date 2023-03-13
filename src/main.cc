#include "tokenize.hh"
#include <memory>

using namespace std;
using tokenize::TokenInfo;
using tokenize::Tokenizer;

int main(int argc, char** argv, char** environ) {
  Tokenizer tokenize = Tokenizer(stdin);

  for (auto token=tokenize.next();
       token->type != lex::token["ENDMARKER"];
       token=tokenize.next())
    if (token->type == lex::token["ERRORTOKEN"])
      return EXIT_FAILURE;

  return EXIT_SUCCESS;
}
