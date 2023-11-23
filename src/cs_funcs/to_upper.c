#include "../string_funcs/s21_string.h"
#include "cs_string.h"

void *to_upper(const char *str) {
  if (!str) return NULL;
  size_t len = s21_strlen(str) + 1;
  char *new_str = malloc(len * sizeof(char));

  if (new_str) {
    for (int i = 0; i < len; i++) {
      if (str[i] >= 'a' && str[i] <= 'z')
        new_str[i] = str[i] + 'A' - 'a';
      else
        new_str[i] = str[i];
    }
  }

  return new_str;
}