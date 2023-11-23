#include "file.h"

void clear_file(const char *path) {
  FILE *fp = fopen(path, "w");

  close_file(fp);
}

FILE *file_init(const char *path, const char *mode) {
  FILE *file = fopen(path, mode);

  return file;
}

void close_file(FILE *file) { fclose(file); }

int is_file_exist(const char *path) {
  FILE *file = fopen(path, "r");
  int result = file != NULL;
  if (file) close_file(file);
  return result;
}

long get_file_size(char *path) {
  long result = 0;

  if (is_file_exist(path)) {
    FILE *file = fopen(path, "r");

    fseek(file, 0, SEEK_END);
    result = ftell(file);
    close_file(file);
  }
  return result;
}

int check_file(char *path) {
  int file_state = FILE_OK;

  if (!is_file_exist(path)) {
    log_add(error, "file not exist");
    log_add(error, path);
    file_state = FILE_NOT_EXIST;
  } else {
    FILE *file = fopen(path, "r");

    if (!get_file_size(path)) {
      log_add(info, "file empty");
      log_add(info, path);
      file_state = FILE_EMPTY;
    }

    close_file(file);
  }

  return file_state;
}
