#include "mrkd.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int arg_len, char *argv[]) {
  config config = parse_args(arg_len, argv);
  printf("Parsed Args\n .exit: %d\n .source = %s\n .source_type = %d\n "
         ".verbose = %d\n .dir_depth = %d\n .output_format = %d\n",
         config.exit, config.source, config.source_type, config.verbose,
         config.dir_depth, config.output_format);

  if (config.exit)
    return 0;

  return 0;
}

config parse_args(int arg_length, char *argv[]) {
  config config = {.source = NULL,
                   .source_type = STR,
                   .verbose = 0,
                   .dir_depth = 1,
                   .output_format = HTML,
                   .exit = 0};

  if (arg_length == 1) {
    print_help(argv[0]);
    config.exit = 1;
    return config;
  }

  for (int i = 1; i < arg_length; i++) {
    // looking for help
    char *chunk = argv[i];

    if (strcmp(chunk, "-h") == 0 || strcmp(chunk, "--help") == 0) {
      print_help(argv[0]);
      config.exit = 1;
      return config;
    }

    if (strcmp(chunk, "-s") == 0 || strcmp(chunk, "--source") == 0) {
      char *path = argv[i + 1];
      i++;
      config.source = path;
      // TODO: check the source type
      continue;
    }

    if (strcmp(chunk, "-d") == 0 || strcmp(chunk, "--dir-depth") == 0) {
      int depth = atoi(argv[i + 1]);
      i++;
      config.dir_depth = depth;
      continue;
    }

    if (strcmp(chunk, "-v") == 0 || strcmp(chunk, "--verbose") == 0) {
      config.verbose = 1;
      continue;
    }

    if (strcmp(chunk, "-o") == 0 || strcmp(chunk, "--output-format") == 0) {
      char *output_format = argv[i + 1];

      if (strcmp(output_format, "HTML") == 0) {
        config.output_format = HTML;
        i++;
        continue;
      }

      if (strcmp(output_format, "AST") == 0) {
        config.output_format = AST;
        i++;
        continue;
      }

      printf("[%s] is not a valid output format.\nOnly 'HTML' and 'AST' "
             "output format are supported.\n\n",
             output_format);
      config.exit = 1;
      print_help(argv[0]);
      return config;
    }

    printf("invalid option: [%s] \n", chunk);
    config.exit = 1;
    print_help(argv[0]);
    return config;
  }

  return config;
}

void print_help(char *program_name) {
  int gap = 30;

  printf("Usage: %s [OPTIONS] [VALUE]\n\n", program_name);
  printf("Options: \n");
  printf("%*s %s\n", -gap, "-h, --help ", "Show this help message");
  printf("%*s %s\n", -gap, "-s, --source <path>",
         "String, file_path, dir_path to parse");
  printf("%*s %s\n", -gap, "-v, --verbose", "Prints every step in verbosly");
  printf("%*s %s\n", -gap, "-d, --dir-depth <depth>",
         "Depth of dir to search upto when source is "
         "dir_path defaults to 1");
  printf("%*s %s\n", -gap, "-o, --output-format <format>",
         "Specify output format either 'AST' or "
         "'HTML' defaults to 'HTML'");
}
