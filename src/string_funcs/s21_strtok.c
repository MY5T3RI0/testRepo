#include "s21_string.h"

char *s21_strtok(char *str, const char *delim) {
  static char *last = NULL;
  if (str) last = str;
  char *start = last;
  int is_empty = 1;

  while (last && is_empty) {
    last = s21_strpbrk(last, delim);
    if (last) {
      *last = '\0';
      if (s21_strlen(start))
        is_empty = 0;
      else
        start++;
      last++;
    }
  }

  return start;
}