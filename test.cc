#include "tokenize.hh"

int main(int argc, char** argv, char** environ) {
  for (auto token : tokenize::File(stdin)) {
    token.dump(false);
    //fwrite(token.raw_value.c_str(), sizeof(char), token.raw_value.length(), stdout);
  }

  return EXIT_SUCCESS;
}
