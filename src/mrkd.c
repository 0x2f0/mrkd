#include "mrkd.h"
#include "compat.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

int main(int arg_len, char *argv[]) {
  config config = parse_args(arg_len, argv);

  if (config.exit)
    return 0;

  parse(config);

  return 0;
}

void parse(config config) {
  for (int i = 0; i < config.source.count; i++) {
    source source = config.source.items[i];
    printf("source[%d] = %s", i, source.source);
  }
  return;
}

config parse_args(int arg_length, char *argv[]) {
  config config = {.source = {},
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
      if (i + 2 > arg_length) {
        printf("No <path> provided for %s flag.\n\n", chunk);
        printf("CORRECT SIGNATURE:\n");
        printf("%*s %s\n", -HELP_GAP, "-s, --source <path>",
               "String, file_path, dir_path to parse");
        config.exit = 1;
        return config;
      }

      char *path = argv[i + 1];
      i++;

      source parsed_source = get_source(path);
      da_append(config.source, parsed_source);
      continue;
    }

    if (strcmp(chunk, "-d") == 0 || strcmp(chunk, "--dir-depth") == 0) {
      if (i + 2 > arg_length) {
        printf("No <depth> provided for %s flag.\n\n", chunk);
        printf("CORRECT SIGNATURE:\n");
        printf("%*s %s\n", -HELP_GAP, "-d, --dir-depth <depth>",
               "Depth of dir to search upto when source is "
               "dir_path defaults to 1");
        config.exit = 1;
        return config;
      }

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
      if (i + 2 > arg_length) {
        printf("No <format> provided for %s flag.\n\n", chunk);
        printf("CORRECT SIGNATURE:\n");
        printf("%*s %s\n", -HELP_GAP, "-o, --output-format <format>",
               "Specify output format either 'AST' or "
               "'HTML' defaults to 'HTML'");
        config.exit = 1;
        return config;
      }

      char *output_format = argv[i + 1];

      if (strcasecmp(output_format, "HTML") == 0) {
        config.output_format = HTML;
        i++;
        continue;
      }

      if (strcasecmp(output_format, "AST") == 0) {
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
  printf("Usage: %s [OPTIONS] [VALUE]\n\n", program_name);
  printf("Options: \n");
  printf("%*s %s\n", -HELP_GAP, "-h, --help ", "Show this help message");
  printf("%*s %s\n", -HELP_GAP, "-s, --source <path>",
         "String, file_path, dir_path to parse");
  printf("%*s %s\n", -HELP_GAP, "-v, --verbose",
         "Prints every step in verbosly");
  printf("%*s %s\n", -HELP_GAP, "-d, --dir-depth <depth>",
         "Depth of dir to search upto when source is "
         "dir_path defaults to 1");
  printf("%*s %s\n", -HELP_GAP, "-o, --output-format <format>",
         "Specify output format either 'AST' or "
         "'HTML' defaults to 'HTML'");
}

// treats path as string if it doesnot exit.
source get_source(char *path) {
  struct stat path_stat;
  source path_source = {.source = path};

  if (stat(path, &path_stat) != 0) {
    path_source.source_type = STR;
    return path_source;
  }

  if (S_ISDIR(path_stat.st_mode)) {
    path_source.source_type = DIR_PATH;
    return path_source;
  }

  path_source.source_type = FILE_PATH;
  return path_source;
}
