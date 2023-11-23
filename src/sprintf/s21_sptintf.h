#pragma once
#ifndef s21_string
#define s21_string

#include <math.h>
#include <stdarg.h>

#include "../common/const.h"
#include "../string_funcs/s21_string.h"
#include "string_format.h"

int sprintf(char *str, const char *format, ...);
int handle_spec(char *str, const char *format, va_list arg);
void get_len(FORMAT *form, char sym, int *i);
void get_flags(FORMAT *form, char *format, int *i);
void get_specifier(FORMAT *form, char sym, int *i);
void get_precision(FORMAT *form, char *format, int *i);
void get_width(FORMAT *form, char *format, int *i);
int s21_atoi(char *str);

#endif