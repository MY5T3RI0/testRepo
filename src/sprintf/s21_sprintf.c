#include "s21_sptintf.h"

int sprintf(char* str, const char* format, ...) {
  size_t format_len = s21_strlen(format) + 1;
  va_list arg;
  va_start(arg, format);

  int i = 0;
  for (; i < format_len; i++) {
    if (format[i] == '%')
      i += handle_spec(str, format + i + 1, arg);
    else
      str[i] = format[i];
  }

  va_end(arg);
  return i;
}

int handle_spec(char* str, const char* format, va_list arg) {
  FORMAT form = (FORMAT){0, 0, 0, 0, 0};

  int i = 0;
  get_flags(&form, (char*)&format[i], &i);
  get_width(&form, (char*)&format[i], &i);
  get_precision(&form, (char*)&format[i], &i);
  get_len(&form, format[i], &i);
  get_specifier(&form, format[i], &i);

  return i;
}

void get_len(FORMAT* form, char sym, int* i) {
  switch (sym) {
    case 'h':
      form->len |= len_h;
      (*i)++;
      break;
    case 'l':
      form->len |= len_l;
      (*i)++;
      break;
    case 'L':
      form->len |= len_L;
      (*i)++;
      break;
  }
}

void get_flags(FORMAT* form, char* format, int* i) {
  int res = 1;
  while (res) {
    switch (format[*i]) {
      case '-':
        form->flags |= flag_minus;
        (*i)++;
        break;
      case '+':
        form->flags |= flag_plus;
        (*i)++;
        break;
      case ' ':
        form->flags |= flag_space;
        (*i)++;
        break;
      case '#':
        form->flags |= flag_sharp;
        (*i)++;
        break;
      case '0':
        form->flags |= flag_0;
        (*i)++;
        break;
      default:
        res = 0;
        break;
    }
  }
}

void get_specifier(FORMAT* form, char sym, int* i) {
  (*i)++;
  switch (sym) {
    case 'c':
      form->specifier |= spec_c;
      break;
    case 'd':
      form->specifier |= spec_d;
      break;
    case 'i':
      form->specifier |= spec_i;
      break;
    case 'e':
      form->specifier |= spec_e;
      break;
    case 'E':
      form->specifier |= spec_E;
      break;
    case 'f':
      form->specifier |= spec_f;
      break;
    case 'g':
      form->specifier |= spec_g;
      break;
    case 'G':
      form->specifier |= spec_G;
      break;
    case 'o':
      form->specifier |= spec_o;
      break;
    case 's':
      form->specifier |= spec_s;
      break;
    case 'u':
      form->specifier |= spec_u;
      break;
    case 'x':
      form->specifier |= spec_x;
      break;
    case 'X':
      form->specifier |= spec_X;
      break;
    case 'p':
      form->specifier |= spec_p;
      break;
    case 'n':
      form->specifier |= spec_n;
      break;
    case '%':
      form->specifier |= spec_percent;
      break;
  }
}

void get_precision(FORMAT* form, char* format, int* i) {
  if (format[0] == '.') {
    if (format[1] == '*')
      *i += 2;
    else {
      char buff[25] = {0};
      int j = 0;

      while (s21_strpbrk(&format[++j], "1234567890")) {
        buff[j - 1] = format[j];
      }

      int number = s21_atoi(buff);
      if (number >= 0) {
        form->precision = number;
        *i += j;
      }
    }
  }
}

void get_width(FORMAT* form, char* format, int* i) {
  if (format[0] == '*')
    *i += 1;
  else {
    char buff[25];
    int j = -1;
    char nums[] = "1234567890";
    while (s21_strchr(nums, format[++j])) {
      buff[j] = format[j];
    }

    if (j > 0) {
      int number = s21_atoi(buff);
      if (number >= 0) {
        form->width = number;
        *i += j;
      }
    }
  }
}

int s21_atoi(char* str) {
  size_t len = s21_strlen(str);
  int res = 0;

  for (int i = len - 1; i >= 0; i--) {
    res += (str[i] - '0') * pow(10, len - i - 1);
  }

  return res;
}