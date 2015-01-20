#include "emerald.h"

int main (int argc, char *argv[]) {
  if (argc == 1) {
    return start_repl();
  } else {
    return parse_cli_arguments(argc, argv);
  }
}

int start_repl () {
  printf("REPL not implemented. Specify a source file to interpret.\n");
  return 1;
}


int parse_cli_arguments (int argc, char* argv[]) {
  // for now assume one filename, no switches
  char* filename = argv[1];
  eval(filename);
  return 0;
}

void eval (char* filename) {
  int size;
  char* code = readfile(filename, &size);
  printf("%s", code);

  em_lexer lexer;
  lexer_init(&lexer, code, filename);
  lexer_scan(&lexer);

}
