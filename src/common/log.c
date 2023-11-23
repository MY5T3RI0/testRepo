#include "log.h"

#include <stdlib.h>
#include <string.h>

#include "file.h"

void log_add(log_type type, char *message) {
  FILE *file = fopen("log.txt", "a");
  char *prefix = get_log_type(type);

  fprintf(file, "%s %s %s\n", prefix, __TIME__, message);

  fclose(file);
  free(prefix);
}

void log_add_status(char *message, int status) {
  FILE *file = fopen("log.txt", "a");
  char *prefix = get_log_type(debug);

  fprintf(file, "%s %s %s exited with status code: %d\n", prefix, __TIME__,
          message, status);

  fclose(file);
  free(prefix);
}

char *get_log_type(log_type type) {
  char *prefix = (char *)malloc(256 * sizeof(char));
  switch (type) {
    case debug:
      strcpy(prefix, "[DEBUG] ");
      break;
    case info:
      strcpy(prefix, "[INFO] ");
      break;
    case warning:
      strcpy(prefix, "[WARNING] ");
      break;
    case error:
      strcpy(prefix, "[ERROR] ");
      break;
    default:
      break;
  }

  return prefix;
}

void clear_log() { clear_file("log.txt"); }