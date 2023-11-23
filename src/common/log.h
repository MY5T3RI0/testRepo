#pragma once
#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

typedef enum LOG_TYPE { debug, info, warning, error } log_type;

void log_add(log_type type, char* message);
void log_add_status(char* message, int status);
char* get_log_type(log_type type);
void clear_log();

#endif