#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 1024

struct options {
  char *pattern;
  int e;
  int i;
  int v;
  int c;
  int l;
  int n;
};

struct options opts = {0};

#endif
