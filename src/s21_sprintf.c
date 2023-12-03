#include "s21_string.h"

int s21_sprintf(char* str, const char* format, ...) {
  s21_size_t format_len = s21_strlen(format) + 1;
  va_list arg;
  va_start(arg, format);

  s21_size_t i = 0;
  int j = 0;
  for (; i < format_len; i++) {
    if (format[i] == '%')
      i += handle_spec(&str[j], format + i + 1, arg, &j);
    else
      str[j++] = format[i];
  }

  va_end(arg);
  return j > 0 ? j - 1 : 0;
}

int handle_spec(char* str, const char* format, va_list arg, int* j) {
  FORMAT form = (FORMAT){0, 0, 0, 0, 0, 0};

  int i = 0;
  get_flags(&form, (char*)&format[i], &i);
  get_width(&form, (char*)&format[i], &i, arg);
  get_precision(&form, (char*)&format[i], &i, arg);
  get_len(&form, format[i], &i);
  get_specifier(&form, format[i], &i);

  format_spec(str, &form, arg, j);

  return i;
}

void format_spec(char* str, FORMAT* form, va_list arg, int* j) {
  if (form->specifier & spec_c) {
    format_char(str, form, arg, j);
  } else if (form->specifier & (spec_d | spec_i)) {
    format_decimal(str, form, arg, j);
  } else if (form->specifier & spec_u) {
    format_unsigned(str, form, arg, j);
  } else if (is_float(form)) {
    format_float(str, form, arg, j);
  } else if (is_nradix(form)) {
    format_nradix(str, form, arg, j);
  } else if (form->specifier & spec_s) {
    format_string(str, form, arg, j);
  } else if (form->specifier & spec_p) {
    format_pointer(str, form, arg, j);
  } else if (form->specifier & spec_percent) {
    format_percent(str, j);
  }
}

void format_nradix(char* str, FORMAT* form, va_list arg, int* j) {
  int radix = 16;
  int shift = 0;

  if (form->specifier & spec_o) radix = 8;

  unsigned long long num = va_arg(arg, unsigned long long);
  if (form->len & len_h)
    num = (unsigned short)num;
  else if (form->len & len_l)
    num = (unsigned long)num;
  else if (!form->len)
    num = (unsigned)num;

  char buff[25] = {0};
  s21_size_t num_size = s21_utoa(num, buff, radix);
  if (form->specifier & spec_X) upper(buff);
  s21_size_t precision =
      num_size > form->precision ? num_size : form->precision;
  int width = form->width - precision;
  if (form->flags & flag_sharp) width -= radix / 8;

  for (int i = 0; i < width && !(form->flags & flag_minus); i++)
    str[shift++] = ' ';

  if (form->flags & flag_sharp) {
    if (form->specifier & spec_o) {
      s21_strncpy(&(str[shift]), "0", 1);
      shift++;
    } else if (form->specifier & spec_x) {
      s21_strncpy(&(str[shift]), "0x", 2);
      shift += 2;
    } else if (form->specifier & spec_X) {
      s21_strncpy(&(str[shift]), "0X", 2);
      shift += 2;
    }
  }

  s21_size_t nulls_count =
      form->precision >= num_size ? form->precision - num_size : 0;
  for (s21_size_t i = 0; i < nulls_count; i++) str[shift++] = '0';

  s21_strncpy(&(str[shift]), buff, num_size);
  (*j) += num_size + shift;
}

void format_float(char* str, FORMAT* form, va_list arg, int* j) {
  int shift = 0;
  int notation = 0;
  double num = va_arg(arg, double);
  int positive_notation = 1;
  if (!(form->len & len_L)) num = (double)num;
  double temp = num;
  char buff[30] = {0};

  notation = calculate_notation(notation, &temp, &positive_notation);
  int total_precision = form->is_precision ? form->precision : 6;
  int total_notation = notation * (positive_notation ? 1 : -1);

  if (form->specifier & (spec_g | spec_G))
    calculate_precision(form, total_notation, total_precision);
  if (form->specifier & spec_e || form->specifier & spec_E) num = temp;

  s21_size_t num_size =
      s21_ftoa(num, buff, form->is_precision ? form->precision : 6);
  s21_size_t precision =
      num_size > form->precision ? num_size : form->precision;
  int width = form->width - precision;
  if (form->flags & flag_plus || form->flags & flag_space) width--;

  for (int i = 0; i < width && !(form->flags & flag_minus); i++)
    str[shift++] = form->flags & flag_0 && !(form->is_precision) ? '0' : ' ';

  if (form->flags & flag_plus && num > 0)
    str[shift++] = '+';
  else if (form->flags & flag_space && num > 0)
    str[shift++] = ' ';

  s21_size_t nulls_count =
      form->precision >= num_size ? form->precision - num_size : 0;
  for (s21_size_t i = 0; i < nulls_count; i++) str[shift++] = '0';

  if (form->specifier & (spec_G | spec_g) && form->flags & flag_sharp)
    set_nulls(buff, form);

  s21_strncpy(&(str[shift]), buff, s21_strlen(buff));
  shift += s21_strlen(buff);

  if (form->is_precision && form->flags & flag_sharp && form->precision == 0)
    str[shift++] = '.';

  if (form->specifier & spec_e || form->specifier & spec_E) {
    str[shift++] = form->specifier & spec_e ? 'e' : 'E';
    str[shift++] = positive_notation ? '+' : '-';
    if (notation < 10) str[shift++] = '0';
    shift += s21_itoa(notation, &(str[shift]), 10);
  }

  (*j) += shift;
}

void format_decimal(char* str, FORMAT* form, va_list arg, int* j) {
  int shift = 0;

  long long num = va_arg(arg, long long);
  if (form->len & len_h)
    num = (short)num;
  else if (form->len & len_l)
    num = (long)num;
  else if (!form->len)
    num = (int)num;

  char buff[25] = {0};
  s21_size_t num_size = s21_itoa(num, buff, 10);
  s21_size_t precision =
      num_size > form->precision ? num_size : form->precision;
  int width = form->width - precision;
  if (form->flags & flag_plus || form->flags & flag_space) width--;

  for (int i = 0; i < width && !(form->flags & flag_minus); i++)
    str[shift++] = form->flags & flag_0 && !(form->is_precision) ? '0' : ' ';
  if (form->flags & flag_plus && num > 0)
    str[shift++] = '+';
  else if (form->flags & flag_space && num > 0)
    str[shift++] = ' ';

  s21_strncpy(&(str[shift]), buff, num_size);
  (*j) += num_size + shift;
}

void format_unsigned(char* str, FORMAT* form, va_list arg, int* j) {
  int shift = 0;

  unsigned long long num = va_arg(arg, unsigned long long);
  if (form->len & len_h)
    num = (unsigned short)num;
  else if (form->len & len_l)
    num = (unsigned long)num;
  else if (!form->len)
    num = (unsigned)num;

  char buff[25] = {0};
  s21_size_t num_size = s21_utoa(num, buff, 10);
  s21_size_t precision =
      num_size > form->precision ? num_size : form->precision;
  int width = form->width - precision;

  for (int i = 0; i < width && !(form->flags & flag_minus); i++)
    str[shift++] = form->flags & flag_0 && !(form->is_precision) ? '0' : ' ';

  s21_size_t nulls_count =
      form->precision >= num_size ? form->precision - num_size : 0;
  for (s21_size_t i = 0; i < nulls_count; i++) str[shift++] = '0';

  s21_strncpy(&(str[shift]), buff, num_size);
  (*j) += num_size + shift;
}

void format_pointer(char* str, FORMAT* form, va_list arg, int* j) {
  int shift = 2;
  s21_strncpy(str, "0x", 2);
  unsigned long num = va_arg(arg, unsigned long);
  char buff[25] = {0};
  int num_size = s21_utoa(num, buff, 16);

  for (int i = 0;
       i < form->width - num_size - shift && !(form->flags & flag_minus); i++)
    str[shift++] = ' ';

  for (int i = 0; i < num_size; i++) str[shift++] = buff[i];

  (*j) += shift;
}

void format_char(char* str, FORMAT* form, va_list arg, int* j) {
  int sym = va_arg(arg, int);
  int shift = 0;
  if (!(form->len & len_l)) sym = (char)sym;

  for (int i = 0; i < form->width - shift && !(form->flags & flag_minus); i++)
    str[shift++] = ' ';

  str[shift++] = sym;
  (*j) += shift;
}

void format_string(char* str, FORMAT* form, va_list arg, int* j) {
  char* new_str = va_arg(arg, char*);
  int shift = 0;
  if (!(form->len & len_l)) new_str = (char*)new_str;
  int precision = s21_strlen(new_str);
  if (form->is_precision && s21_strlen(new_str) > form->precision)
    precision = form->precision;

  int width = form->width - precision;

  for (int i = 0; i < width && !(form->flags & flag_minus); i++)
    str[shift++] = ' ';

  for (int i = 0; i < precision; i++) str[shift++] = new_str[i];

  (*j) += shift;
}

void format_percent(char* str, int* j) {
  str[0] = '%';
  (*j)++;
}

int is_decimal(FORMAT* form) {
  return form->specifier & (spec_d | spec_i | spec_u);
}

int is_float(FORMAT* form) {
  return form->specifier & (spec_e | spec_E | spec_f | spec_g | spec_G);
}

int is_nradix(FORMAT* form) {
  return form->specifier & (spec_o | spec_X | spec_x);
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

void get_precision(FORMAT* form, char* format, int* i, va_list arg) {
  if (format[0] == '.') {
    if (format[1] == '*') {
      *i += 2;
      form->precision = va_arg(arg, int);
      form->is_precision = 1;
    } else {
      char buff[25] = {0};
      int j = 0;
      char nums[] = NUMS_STR;
      while (s21_strchr(nums, format[++j])) {
        buff[j - 1] = format[j];
      }

      int number = s21_atoi(buff);
      if (number >= 0) {
        form->precision = number;
        form->is_precision = 1;
        *i += j;
      }
    }
  }
}

void get_width(FORMAT* form, char* format, int* i, va_list arg) {
  if (format[0] == '*') {
    form->width = va_arg(arg, int);
    *i += 1;
  } else {
    char buff[25] = {0};
    int j = -1;
    char nums[] = NUMS_STR;
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

s21_size_t s21_itoa(long long num, char* str, int radix) {
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

s21_size_t s21_utoa(unsigned long long num, char* str, int radix) {
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

s21_size_t s21_ftoa(long double num, char* str, size_t precision) {
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

char* upper(char* str) {
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

void set_nulls(char* str, FORMAT* form) {
  s21_size_t len = s21_strlen(str);
  int is_end = 0;

  for (s21_size_t i = 0; i < len && !is_end; i++) {
    if (str[len - i - 1] == '0')
      str[len - i - 1] = '\0';
    else
      is_end = 1;
  }

  s21_memset(&(str[s21_strlen(str)]), '0', form->precision);
}

int g_selector(int p, int x) { return p > x && x >= -4; }

int calculate_notation(int notation, double* temp, int* positive_notation) {
  while (*temp > 10) {
    *temp /= 10;
    notation++;
  }
  while (*temp < 1) {
    *temp *= 10;
    notation++;
    *positive_notation = 0;
  }

  return notation;
}

void calculate_precision(FORMAT* form, int total_notation,
                         int total_precision) {
  if (!g_selector(total_precision, total_notation)) {
    form->specifier |= (form->specifier & spec_g ? spec_e : spec_E);
    form->is_precision = 1;
    form->precision = total_precision - 1 > 0 ? total_precision - 1 : 0;
  } else {
    form->is_precision = 1;
    form->precision = total_precision - (total_notation + 1);
  }
}