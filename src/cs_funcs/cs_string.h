#pragma once
#ifndef cs_string
#define cs_string

#include <stdlib.h>

void *to_upper(const char *str);
void *to_lower(const char *str);
void *insert(const char *src, const char *str, size_t start_index);
void *trim(const char *src, const char *trim_chars);

#endif