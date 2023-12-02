#include "s21_string.h"

void *s21_memchr(const void *str, int c, size_t n) {
  const unsigned char *result = str;
  void *chr = NULL;
  for (size_t i = 0; i < n && !chr; i++)
    if (*(result + i) == c) chr = (void *)(result + i);

  return chr;
}

int s21_memcmp(const void *str1, const void *str2, size_t n) {
  const unsigned char *str_1 = str1;
  const unsigned char *str_2 = str2;
  int res = 0;

  for (size_t i = 0; i < n && !res; i++)
    if (*(str_1 + i) != *(str_2 + i)) res = *(str_1 + i) - *(str_2 + i);

  return res;
}

void *s21_memcpy(void *dest, const void *src, size_t n) {
  unsigned char *destination = dest;
  const unsigned char *source = src;
  size_t len = s21_strlen(src) < n ? s21_strlen(src) + 1 : n;
  for (size_t i = 0; i < len; i++) {
    destination[i] = *(source + i);
  }

  return dest;
}

void *s21_memset(void *str, int c, size_t n) {
  unsigned char *temp = str;
  for (size_t i = 0; i < n; i++) temp[i] = (unsigned char)c;

  return str;
}

char *s21_strncat(char *dest, const char *src, size_t n) {
  size_t start = s21_strlen(dest);
  size_t end = start + s21_strlen(src) + 1;
  size_t len = end < n ? end : n;
  size_t size = start + len;

  for (size_t i = 0; i < len; i++) dest[start + i] = src[i];
  if (s21_strlen(dest) > size) dest[size] = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  if (!c) return (char *)str + s21_strlen(str);
  void *chr = NULL;

  for (size_t i = 0; str[i] && !chr; i++)
    if (*(str + i) == c) chr = (char *)str + i;

  return chr;
}

int s21_strncmp(const char *str1, const char *str2, size_t n) {
  size_t end =
      s21_strlen(str1) > s21_strlen(str2) ? s21_strlen(str1) : s21_strlen(str2);
  size_t len = end < n ? end : n;
  int res = 0;

  for (size_t i = 0; i < len && !res; i++)
    if (*(str1 + i) != *(str2 + i)) res = *(str1 + i) - *(str2 + i);

  return res > 0 ? 1 : res < 0 ? -1 : 0;
}

char *s21_strncpy(char *dest, const char *src, size_t n) {
  size_t end =
      s21_strlen(src) > s21_strlen(dest) ? s21_strlen(src) : s21_strlen(dest);
  size_t len = end < n ? end : n;

  for (size_t i = 0; i < len; i++) dest[i] = *(src + i);

  return dest;
}

size_t s21_strcspn(const char *str1, const char *str2) {
  size_t res = 0;
  int is_searched = 0;
  size_t len = s21_strlen(str1);

  for (size_t i = 0; i < len && !is_searched; i++)
    if (s21_strchr(str2, str1[i])) {
      res = i;
      is_searched = 1;
    }

  return is_searched ? res : len;
}

char *s21_strerror(int errnum) {
  static char error[STRERR_MAX];
  ARRAY;

  if (errnum > ERR_MAX) {
    char buff[4096] = {0};
    s21_sprintf(buff, "%s%d", ERROR, errnum);
    s21_strncpy(error, buff, s21_strlen(buff));
  } else
    s21_strncpy(error, errlist[errnum], s21_strlen(errlist[errnum]));

  return error;
}

size_t s21_strlen(const char *str) {
  size_t len = 0;
  for (; str[len]; len++)
    ;

  return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  size_t i = 0;
  size_t len = s21_strlen(str1);

  for (char *res = s21_strchr(str2, str1[0]); i < len && !res;)
    res = s21_strchr(str2, str1[++i]);

  return i < len ? (char *)&str1[i] : NULL;
}

char *s21_strrchr(const char *str, int c) {
  void *chr = NULL;
  size_t len = s21_strlen(str);

  for (size_t i = 0; i < len && !chr; i++)
    if (*(str + len - i - 1) == c) chr = (char *)str + len - i - 1;

  return chr;
}

char *s21_strstr(const char *haystack, const char *needle) {
  size_t haystack_len = s21_strlen(haystack);
  size_t needle_len = s21_strlen(needle);
  char *current = (char *)haystack;
  char *temp = NULL;
  int is_searched = 0;

  if (!(*needle)) is_searched = 1;

  for (size_t i = 0; i < haystack_len && !is_searched && current; i++) {
    temp = s21_strchr(current, needle[0]);
    if (current == temp)
      current++;
    else
      current = temp;
    if (current) is_searched = !s21_strncmp(current, needle, needle_len);
  }

  return is_searched ? current : NULL;
}

char *s21_strtok(char *str, const char *delim) {
  if (str && !str[0]) return NULL;
  static char *last = NULL;
  if (str) last = str;
  char *start = last;
  int is_empty = 1;

  while (last && is_empty) {
    last = s21_strpbrk(last, delim);
    if (last) {
      *last = '\0';
      if (*start != 0)
        is_empty = 0;
      else
        start++;
      last++;
    }
  }

  return start;
}

size_t s21_strspn(const char *str1, const char *str2) {
  size_t res = 0;

  while (*s21_strchr(str2, str1[res])) res++;

  return res;
}