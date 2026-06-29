#include "mrkd.h"
#include <stdio.h>

int main(int arg_len, char *argv[]) {
  Config config = parse_args(arg_len, argv);
  if (config.exit)
    return 0;

  return 0;
}

Config parse_args(int arg_length, char *argv[]) {
  Config config = {.source = NULL,
                   .source_type = NULL,
                   .verbose = 0,
                   .dir_depth = 1,
                   .output_format = HTML,
                   .exit = 0};

  if (arg_length == 1) {
    print_help(argv[0]);
    config.exit = 1;
    return config;
  }

  return config;
}

void print_help(char *program_name) {
  printf("Usage: %s [OPTIONS]\n", program_name);
  printf("Options: \n");
  printf("-h, --help                      Show this help message\n");
  printf("-s, --source <path>             string, file_path, "
         "dir_path to parse\n");
  printf("-d, --dir_depth <depth>         depth of dir to search upto "
         "when source is dir_path defaults to 1\n");
  printf("-o, --output_format <format>    parsed ouptut format either "
         "'AST' or 'HTML' "
         "defaults to 'HTML'\n");
}
