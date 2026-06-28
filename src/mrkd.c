#include "mrkd.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  parse_args(argc, argv);
  return 0;
}

char *parse_args(int arg_length, char *argv[]) {
  char *parsedArgs;
  print_help(argv[0]);
  return parsedArgs;
}

void print_help(char *of) {
  char *msg = "\nWelcome to the help page of mrkd;\n"
              "It is a small markdown renderer written in c,"
              "which takes in either one of markdown file, directory, string "
              "and returns a AST in json or Rendered document"
              "as well as rendered html document.";
  printf("%s", msg);
}
