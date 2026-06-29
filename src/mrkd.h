#ifndef MRKD_H
#define MRKD_H

enum SOURCE_TYPE { STR, FILE_PATH, DIR_PATH };
enum OUTPUT_FORMAT { AST, HTML };

typedef struct {
  // can be a file, folder or just raw string
  char *source;
  enum SOURCE_TYPE *source_type;
  int verbose;
  // depth of dir to search for when source_type is DIR_PATH defaults to 1
  int dir_depth;
  // default to AST
  enum OUTPUT_FORMAT output_format;
	// to exit the program.
	int exit;
} Config;

Config parse_args(int arg_length, char *argv[]);
/* TODO:implement of feature */
void print_help(char *program_name);

#endif
