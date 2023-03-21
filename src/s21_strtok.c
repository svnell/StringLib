#include "s21_string.h"

static int s21_delim(char c, const char *delim) {
  int flag = 0;
  while (*delim != '\0') {
    if (c == *delim) flag = 1;
    delim++;
  }
  return flag;
}

char *s21_strtok(char *s, const char *delim) {
  static char *st_ch = s21_NULL;
  char *ch_pointer;
  if (!s) s = st_ch;
  if (*s == '\0') {
    ch_pointer = s21_NULL;
  } else {
    while (1) {
      if (s21_delim(*s, delim)) {
        s++;
        continue;
      }
      if (*s == '\0') s = s21_NULL;
      break;
    }
    ch_pointer = s;
    while (s != s21_NULL) {
      if (*s == '\0') {
        st_ch = s;
        break;
      }
      if (s21_delim(*s, delim)) {
        *s = '\0';
        st_ch = s + 1;
        break;
      }
      s++;
    }
  }

  return (ch_pointer);
}
