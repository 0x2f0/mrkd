#pragma once
#include <stddef.h>
#ifdef _WIN32
#define strcasecmp _stricmp
#endif

// Best practice: Define a macro for reusability
#define len(x) (sizeof(x) / sizeof((x)[0]))

// gap between flag and description.
#define HELP_GAP 30

// defines a dynamic array struct
#define da_struct(type, name)                                                  \
  typedef struct {                                                             \
    type *items;                                                               \
    size_t count;                                                              \
    size_t capacity;                                                           \
  } name;

// defines a way to add element to the dynamic array
#define da_append(da_struct, item)                                             \
  do {                                                                         \
    if (da_struct.count >= da_struct.capacity) {                               \
      if (da_struct.capacity == 0)                                             \
        da_struct.capacity = 256;                                              \
      else                                                                     \
        da_struct.capacity *= 2;                                               \
      realloc(da_struct.items, da_struct.capacity * sizeof(*da_struct.items)); \
    }                                                                          \
    da_struct.items[da_struct.count++] = item;                                 \
  } while (0)

enum SOURCE_TYPE { STR, FILE_PATH, DIR_PATH };
enum OUTPUT_FORMAT { HTML, AST };

typedef struct {
  // can be a file, folder or just raw string
  char *source;
  enum SOURCE_TYPE source_type;
} source;

da_struct(source, source_array);

typedef struct {
  int verbose;
  // depth of dir to search for when source_type is DIR_PATH defaults to 1
  int dir_depth;
  // default to AST
  enum OUTPUT_FORMAT output_format;

  // to exit the program.
  int exit;
  source_array source;
} config;

config parse_args(int arg_length, char *argv[]);
void print_help(char *program_name);

// provides the source of the given path.
source get_source(char *path);
