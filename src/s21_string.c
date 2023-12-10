#include "s21_string.h"

void *s21_memchr(const void *str, int c, s21_size_t n) {
  const unsigned char *result = str;
  void *chr = s21_NULL;
  for (s21_size_t i = 0; i < n && !chr; i++)
    if (*(result + i) == c) chr = (void *)(result + i);

  return chr;
}

int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  const unsigned char *str_1 = str1;
  const unsigned char *str_2 = str2;
  int res = 0;

  for (s21_size_t i = 0; i < n && !res; i++)
    if (*(str_1 + i) != *(str_2 + i)) res = *(str_1 + i) - *(str_2 + i);

  return res;
}

void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *destination = dest;
  const unsigned char *source = src;
  s21_size_t len = s21_strlen(src) < n ? s21_strlen(src) + 1 : n;
  for (s21_size_t i = 0; i < len; i++) {
    destination[i] = *(source + i);
  }

  return dest;
}

void *s21_memset(void *str, int c, s21_size_t n) {
  unsigned char *temp = str;
  for (s21_size_t i = 0; i < n; i++) temp[i] = (unsigned char)c;

  return str;
}

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  s21_size_t start = s21_strlen(dest);
  s21_size_t end = start + s21_strlen(src) + 1;
  s21_size_t len = end < n ? end : n;
  s21_size_t size = start + len;

  for (s21_size_t i = 0; i < len; i++) dest[start + i] = src[i];
  if (s21_strlen(dest) > size) dest[size] = '\0';
  return dest;
}

char *s21_strchr(const char *str, int c) {
  if (!c) return (char *)str + s21_strlen(str);
  void *chr = s21_NULL;

  for (s21_size_t i = 0; str[i] && !chr; i++)
    if (*(str + i) == c) chr = (char *)str + i;

  return chr;
}

int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  s21_size_t end =
      s21_strlen(str1) > s21_strlen(str2) ? s21_strlen(str1) : s21_strlen(str2);
  s21_size_t len = end < n ? end : n;
  int res = 0;

  for (s21_size_t i = 0; i < len && !res; i++)
    if (*(str1 + i) != *(str2 + i)) res = *(str1 + i) - *(str2 + i);

  return res > 0 ? 1 : res < 0 ? -1 : 0;
}

char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_size_t end =
      s21_strlen(src) > s21_strlen(dest) ? s21_strlen(src) : s21_strlen(dest);
  s21_size_t len = end < n ? end : n;

  for (s21_size_t i = 0; i < len; i++) dest[i] = *(src + i);

  return dest;
}

s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  int is_searched = 0;
  s21_size_t len = s21_strlen(str1);

  for (s21_size_t i = 0; i < len && !is_searched; i++)
    if (s21_strchr(str2, str1[i])) {
      res = i;
      is_searched = 1;
    }

  return is_searched ? res : len;
}

char *s21_strerror(int errnum) {
  static char error[STRERR_MAX];
  ARRAY;

  if (errnum >= ERR_MAX || errnum < 0) {
    s21_sprintf(error, "%s%d", ERROR, errnum);
  } else {
    int len = s21_strlen(errlist[errnum]);
    s21_strncpy(error, errlist[errnum], len);
    error[len] = '\0';
  }

  return error;
}

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  for (; str[len]; len++)
    ;

  return len;
}

s21_size_t s21_strlen_long(const wchar_t *str) {
  s21_size_t len = 0;
  for (; str[len]; len++)
    ;

  return len;
}

char *s21_strpbrk(const char *str1, const char *str2) {
  s21_size_t i = 0;
  s21_size_t len = s21_strlen(str1);

  for (char *res = s21_strchr(str2, str1[0]); i < len && !res;)
    res = s21_strchr(str2, str1[++i]);

  return i < len ? (char *)&str1[i] : s21_NULL;
}

char *s21_strrchr(const char *str, int c) {
  void *chr = s21_NULL;
  s21_size_t len = s21_strlen(str);

  for (s21_size_t i = 0; i < len && !chr; i++)
    if (*(str + len - i - 1) == c) chr = (char *)str + len - i - 1;

  return chr;
}

char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t haystack_len = s21_strlen(haystack);
  s21_size_t needle_len = s21_strlen(needle);
  char *current = (char *)haystack;
  char *temp = s21_NULL;
  int is_searched = 0;

  if (!(*needle)) is_searched = 1;

  for (s21_size_t i = 0; i < haystack_len && !is_searched && current; i++) {
    temp = s21_strchr(current, needle[0]);
    if (current == temp)
      current++;
    else
      current = temp;
    if (current) is_searched = !s21_strncmp(current, needle, needle_len);
  }

  return is_searched ? current : s21_NULL;
}

char *s21_strtok(char *str, const char *delim) {
  if (str && !str[0]) return s21_NULL;
  static char *last = s21_NULL;
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

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  while (str1[res] && s21_strchr(str2, str1[res])) res++;
  return res;
}

char *s21_strcpy(char *dest, const char *src) {
  for (int i = 0; src[i]; i++) {
    dest[i] = src[i];
  }

  dest[s21_strlen(src)] = '\0';

  return dest;
}

long double s21_strtold(const char *buffer) {
  long double result = 0.0;
  int includesInfNan = includesInfOrNan(buffer);

  if (!includesInfNan) {
    result = s21_atof(buffer);

    if (includesExponent(buffer)) {
      result = applyExponent(result, buffer);
    }
  }

  return (includesInfNan) ? returnInfOrNan(buffer) : result;
}

int caseInsnsSearch(const char *buffer, const char *pat) {
  int isFound = 0;
  int len = (int)s21_strlen(pat);

  for (int i = 0; buffer[i] && !isFound; i++) {
    int counter = 0;
    for (int j = 0; j < len && !isFound; j++) {
      if ((buffer[i] == (pat[j] - 'A') + 'a') ||
          (buffer[i] == (pat[j] - 'a') + 'A') || pat[j] == buffer[i]) {
        counter++;
        i++;
      }

      if (len == counter) {
        isFound = 1;
      }
    }
  }

  return isFound;
}

int includesInfOrNan(const char *buffer) {
  int result = 0;

  int checkInf = caseInsnsSearch(buffer, "inf");
  int checkNan = caseInsnsSearch(buffer, "nan");

  if (checkInf || checkNan) {
    result = 1;
  }

  return result;
}

long double returnInfOrNan(const char *buffer) {
  int res = 0;
  int isFound = 0;

  for (int i = 0; buffer[i] && !isFound; i++) {
    if (buffer[i] == 'i' || buffer[i] == 'I') {
      res = 1;
      isFound = 1;
    }
  }

  return (res == 1) ? INFINITY : NAN;
}

long double applyExponent(long double result, const char *buffer) {
  char sign = '+';
  int exponent = 0;

  for (char *buffPtr = (char *)buffer; *buffPtr; buffPtr++) {
    if (*buffPtr == 'e' || *buffPtr == 'E') {
      sign = *(buffPtr + 1);
      exponent = s21_atoi(buffPtr + 2);
    }
  }

  while (exponent) {
    if (sign == '-') {
      result /= 10.0;
    } else {
      result *= 10.0;
    }

    exponent--;
  }

  return result;
}

int includesExponent(const char *buffer) {
  int result = 0;

  for (char *p = (char *)buffer; *p && !result; p++) {
    if (s21_strspn(p, "eE")) {
      result = 1;
    }
  }

  return result;
}

long double s21_atof(const char *buffer) {
  long double frac = 0.0;
  char *buffPtr = (char *)buffer;

  int minus_sign = (*buffPtr == '-');

  if (*buffPtr == '-' || *buffPtr == '+') {
    buffPtr++;
  }

  long double result = s21_atoi(buffPtr);

  while (isDigit(*buffPtr)) buffPtr++;

  if (*buffPtr == '.') {
    buffPtr++;
    //! вашему вниманию танцы с бубнами с 123.000001

    int trailing_zeros = s21_strspn(buffPtr, "0");
    frac = s21_atoi(buffPtr);
    int temp = (int)frac;

    while (temp) {
      frac /= 10.0;
      temp /= 10;
    }

    while (trailing_zeros) {
      frac /= 10.0;
      trailing_zeros--;
    }
  }

  result += frac;

  return minus_sign ? -result : result;
}

int s21_atoi(char *str) {
  s21_size_t len = s21_strspn(str, NUMS_STR);
  int res = 0;
  int state = 1;

  for (s21_size_t i = 0; i < len && state; i++) {
    if (str[i] < '0' || str[i] > '9')
      state = 0;
    else
      res += (str[i] - '0') * pow(10, len - i - 1);
  }

  return res;
}

s21_size_t s21_itoa(long long num, char *str, int radix) {
  char buff[25] = {0};
  char nums[] = "0123456789abcdef";
  if (num < 0) {
    str[0] = '-';
    num *= -1;
  }
  if (num == 0)
    buff[0] = '0';
  else
    for (int i = 0; num != 0; i++) {
      buff[i] = nums[num % radix];
      num /= radix;
    }

  s21_size_t len = s21_strlen(buff);

  for (s21_size_t i = 0; i < len; i++)
    str[str[0] == '-' ? i + 1 : i] = buff[len - i - 1];

  return str[0] == '-' ? len + 1 : len;
}

s21_size_t s21_utoa(unsigned long long num, char *str, int radix) {
  char buff[25] = {0};
  char nums[] = "0123456789abcdef";

  for (int i = 0; num != 0; i++) {
    buff[i] = nums[num % radix];
    num /= radix;
  }

  s21_size_t len = s21_strlen(buff);

  for (s21_size_t i = 0; i < len; i++) str[i] = buff[len - i - 1];

  return len;
}

s21_size_t s21_ftoa(long double num, char *str, size_t precision) {
  long double x, y;
  s21_size_t res = 0;
  if (num < 0) {
    str[res++] = '-';
    num *= -1;
  }
  y = modfl(num, &x);
  char buff[25] = {0};

  res += s21_itoa(x, &(str[res]), 10);
  if (precision > 0) {
    str[res++] = '.';
    s21_size_t float_size = s21_itoa(roundl(y * pow(10, precision)), buff, 10);
    if (float_size < precision) {
      s21_memset(&(str[res]), '0', precision - float_size);
      res += precision - float_size;
    }
    s21_strncpy(&(str[res]), buff, float_size);
    res += float_size;
  }

  return res;
}

char *upper(char *str) {
  if (!str) return s21_NULL;
  s21_size_t len = s21_strlen(str);

  for (s21_size_t i = 0; i < len; i++) {
    if (str[i] >= 'a' && str[i] <= 'z')
      str[i] = str[i] + 'A' - 'a';
    else
      str[i] = str[i];
  }

  return str;
}