#pragma once
#ifndef s21_string
#define s21_string

#include <math.h>
#include <stdarg.h>

#include "../common/const.h"
#include "../cs_funcs/cs_string.h"
#include "../string_funcs/s21_string.h"
#include "string_format.h"

#define NUMS_STR "0123456789"

int sprintf(char *str, const char *format, ...);
int handle_spec(char *str, const char *format, va_list arg, int *j);
void get_len(FORMAT *form, char sym, int *i);
void get_flags(FORMAT *form, char *format, int *i);
void get_specifier(FORMAT *form, char sym, int *i);
void get_precision(FORMAT *form, char *format, int *i, va_list arg);
void get_width(FORMAT *form, char *format, int *i, va_list arg);
int s21_atoi(char *str);
size_t s21_itoa(long long num, char *str, int radix);
size_t s21_utoa(unsigned long long num, char *str, int radix);
void format_spec(char *str, FORMAT *form, va_list arg, int *j);
int is_decimal(FORMAT *form);
int is_float(FORMAT *form);
int is_nradix(FORMAT *form);
void format_nradix(char *str, FORMAT *form, va_list arg, int *j);
void format_decimal(char *str, FORMAT *form, va_list arg, int *j);
void format_unsigned(char *str, FORMAT *form, va_list arg, int *j);
void format_pointer(char *str, FORMAT *form, va_list arg, int *j);
void format_char(char *str, FORMAT *form, va_list arg, int *j);
void format_string(char *str, FORMAT *form, va_list arg, int *j);
void format_percent(char *str, int *j);

#endif