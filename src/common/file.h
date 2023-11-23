#pragma once
#ifndef FILE_H
#define FILE_H

#define _GNU_SOURCE  // getline
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "const.h"
#include "log.h"

#define MAX_FILE_WIDTH 256

#define MaxPathLength 100
#define MaxFileHeight 1024
#define MaxFileWidth 1024
#define MaxMessageLength 1024
#define FILE_OK 0
#define FILE_EMPTY 1
#define FILE_NOT_EXIST 2

void clear_file(const char *path);
FILE *file_init(const char *path, const char *mode);
void close_file(FILE *file);
int is_file_exist(const char *path);
long get_file_size(char *path);
int check_file(char *path);
int get_file_len(char *path);

#endif