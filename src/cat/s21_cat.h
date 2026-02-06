#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct options {
  int b;
  int n;
  int s;
  int e;
  int t;
  int E;
  int T;
};

struct option long_options[] = {{"number-nonblank", no_argument, 0, 'b'},
                                {"number", no_argument, 0, 'n'},
                                {"squeeze-blank", no_argument, 0, 's'},
                                {0, 0, 0, 0}};

struct options opts = {0};

#endif
