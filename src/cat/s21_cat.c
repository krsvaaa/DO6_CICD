#include "s21_cat.h"

void no_flag(FILE *file) {
  int symb;
  while ((symb = fgetc(file)) != EOF) {
    putchar(symb);
  }
}

void b_n_flag(FILE *file, int n, int *n_count) {
  int symb;
  int line = '\n';
  while ((symb = fgetc(file)) != EOF) {
    if ((line == '\n') && ((symb != '\n') || n == 1)) {
      printf("%6d\t", *n_count);
      *n_count += 1;
    }
    line = symb;
    putchar(symb);
  }
}

void s_flag(FILE *file, int *last_line_empty) {
  int symb;
  int line = '\n';
  int line_count = *last_line_empty;
  while ((symb = fgetc(file)) != EOF) {
    if (symb == '\n') {
      if (line == '\n') {
        line_count += 1;
        if (line_count == 2) {
          putchar('\n');
        }
      } else {
        putchar('\n');
        line_count = 1;
      }
    } else {
      putchar(symb);
      line_count = 0;
    }
    line = symb;
  }
  *last_line_empty = line_count;
}

void E_T_flag(FILE *file, int v, int t) {
  int symb;
  while ((symb = fgetc(file)) != EOF) {
    if (v == 0) {
      if (t == 1 && symb == 9) {
        printf("^I");
      } else if (t == 0 && symb == 10) {
        putchar('$');
        putchar(symb);
      } else {
        putchar(symb);
      }
    } else {
      if (t == 1) {
        if (0 <= symb && symb < 32 && symb != 10) {
          putchar('^');
          putchar(symb + 64);
        } else if (symb == 127) {
          printf("^?");
        } else {
          putchar(symb);
        }
      } else {
        if (symb == 10) {
          putchar('$');
          putchar(symb);
        } else if (symb == 127) {
          printf("^?");
        } else if (0 <= symb && symb < 32 && symb != 9) {
          putchar('^');
          putchar(symb + 64);
        } else {
          putchar(symb);
        }
      }
    }
  }
}

void functions(struct options opts, FILE *file, int n, int t, int v,
               int *n_count, int *last_line_empty) {
  if (opts.b) {
    b_n_flag(file, n, n_count);
  } else if (opts.n) {
    b_n_flag(file, n, n_count);
  } else if (opts.s) {
    s_flag(file, last_line_empty);
  } else if (opts.E) {
    E_T_flag(file, v, t);
  } else if (opts.T) {
    E_T_flag(file, v, t);
  } else if (opts.e) {
    E_T_flag(file, v, t);
  } else if (opts.t) {
    E_T_flag(file, v, t);
  } else {
    no_flag(file);
  }
}

int main(int argc, char *argv[]) {
  int n_count = 1;
  int last_line_empty = 0;
  int opt, index;
  int n = 0;
  int t = 0;
  int v = 0;
  while ((opt = getopt_long(argc, argv, "bnsetET", long_options, &index)) !=
         -1) {
    switch (opt) {
      case 'b':
        opts.b = 1;
        break;
      case 'n':
        opts.n = 1;
        n = 1;
        break;
      case 's':
        opts.s = 1;
        break;
      case 'E':
        opts.E = 1;
        break;
      case 'T':
        opts.T = 1;
        t = 1;
        break;
      case 'e':
        opts.e = 1;
        v = 1;
        break;
      case 't':
        opts.t = 1;
        v = 1;
        t = 1;
        break;
      default:
        fprintf(stderr, "Wrong flag\n");
    }
  }
  if (optind == argc) {
    fprintf(stderr, "Need filename\n");
  } else {
    for (; optind < argc; optind++) {
      FILE *file = fopen(argv[optind], "r");
      if (!file) {
        fprintf(stderr, "Wrong filename\n");
      } else {
        functions(opts, file, n, t, v, &n_count, &last_line_empty);
        fclose(file);
      }
    }
  }

  return 0;
}
