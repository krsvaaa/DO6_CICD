#include "s21_grep.h"

void compile_regex(regex_t *regex, struct options opts) {
  int regex_flags = REG_EXTENDED;

  if (opts.i) {
    regex_flags |= REG_ICASE;
  }

  if (regcomp(regex, opts.pattern, regex_flags) != 0) {
    fprintf(stderr, "Error compiling regex\n");
  }
}

void print_line_with_newline(const char *line) {
  if (line[strlen(line) - 1] != '\n') {
    printf("%s\n", line);
  } else {
    printf("%s", line);
  }
}

void process_flags(const char *line, const char *filename, int line_number,
                   int multiple_files, int match, struct options opts) {
  if (match) {
    if (opts.l) {
      printf("%s\n", filename);
      return;
    }
    if (!opts.c) {
      if (opts.n) {
        if (multiple_files) {
          printf("%s:%d:", filename, line_number);
        } else {
          printf("%d:", line_number);
        }
      } else if (multiple_files) {
        printf("%s:", filename);
      }
      print_line_with_newline(line);
    }
  }
}

void process_lines(FILE *file, regex_t *regex, struct options opts,
                   const char *filename, int multiple_files, int *match_count) {
  char line[MAX_LINE_SIZE];
  int line_number = 0;
  int file_printed = 0;

  while (fgets(line, sizeof(line), file)) {
    line_number++;
    int match = regexec(regex, line, 0, NULL, 0) == 0;

    if (opts.v) {
      match = !match;
    }

    if (match && !file_printed) {
      (*match_count)++;
      if (opts.l) {
        printf("%s\n", filename);
        file_printed = 1;
        return;
      }
    }

    process_flags(line, filename, line_number, multiple_files, match, opts);
  }
}

void process_single_file(const char *filename, struct options opts,
                         int multiple_files, int *total_match_count) {
  FILE *file = fopen(filename, "r");
  if (file) {
    regex_t regex;
    int match_count = 0;
    compile_regex(&regex, opts);
    process_lines(file, &regex, opts, filename, multiple_files, &match_count);

    if (opts.c) {
      if (multiple_files) {
        printf("%s:%d\n", filename, match_count);
      } else {
        printf("%d\n", match_count);
      }
    }

    *total_match_count += match_count;

    regfree(&regex);
    fclose(file);
  } else {
    fprintf(stderr, "Wrong file\n");
  }
}

void process_files(struct options opts, int argc, char **argv) {
  int multiple_files = (argc - optind) > 1;
  int total_match_count = 0;

  for (int i = optind; i < argc; i++) {
    process_single_file(argv[i], opts, multiple_files, &total_match_count);
  }
}

int main(int argc, char *argv[]) {
  int opt;
  int pattern_in_mem = 0;

  while ((opt = getopt(argc, argv, "e:ivcln")) != -1) {
    switch (opt) {
      case 'e':
        opts.e = 1;
        opts.pattern = strdup(optarg);
        pattern_in_mem = 1;
        break;
      case 'i':
        opts.i = 1;
        break;
      case 'v':
        opts.v = 1;
        break;
      case 'c':
        opts.c = 1;
        break;
      case 'l':
        opts.l = 1;
        break;
      case 'n':
        opts.n = 1;
        break;
      default:
        fprintf(stderr, "Wrong flag\n");
    }
  }

  if (!opts.pattern) {
    if (optind < argc) {
      opts.pattern = argv[optind++];
    } else {
      fprintf(stderr, "No pattern\n");
    }
  }

  process_files(opts, argc, argv);

  if (pattern_in_mem) {
    free(opts.pattern);
  }

  return 0;
}
