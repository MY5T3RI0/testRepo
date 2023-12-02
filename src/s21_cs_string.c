#include "s21_string.h"

void *s21_insert(const char *src, const char *str, size_t start_index) {
  if (!src || s21_strlen(src) < start_index || !str) return NULL;

  char *new_str = malloc((s21_strlen(src) + 1) * sizeof(char));

  if (new_str) {
    s21_strcpy(new_str, src);
    s21_strcpy((char *)new_str + start_index, str);
    new_str[s21_strlen(new_str)] = '\0';
  }

  return new_str;
}

void *s21_to_lower(const char *str) {
  if (!str) return NULL;
  size_t len = s21_strlen(str) + 1;
  char *new_str = malloc(len * sizeof(char));

  if (new_str) {
    for (int i = 0; i < len; i++) {
      if (str[i] >= 'A' && str[i] <= 'Z')
        new_str[i] = str[i] - 'A' + 'a';
      else
        new_str[i] = str[i];
    }
  }

  return new_str;
}

void *s21_to_upper(const char *str) {
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

void *s21_trim(const char *src, const char *trim_chars) {
  if (!src || !trim_chars) return NULL;

  size_t start = 0;
  size_t end = s21_strlen(src) + 1;

  if (s21_strchr(trim_chars, src[start]))
    while (s21_strchr(trim_chars, src[++start]))
      ;
  while (s21_strchr(trim_chars, src[--end - 1]))
    ;

  size_t len = end - start;
  char *new_str = malloc((len + 1) * sizeof(char));

  if (new_str) {
    for (int i = start, j = 0; i < end; i++, j++) new_str[j] = src[i];
    new_str[len] = '\0';
  }

  return new_str;
}