#include "s21_string.h"

char *s21_strrchr(const char *str, int c) {
  char *arc = s21_NULL;
  int flag = 0;
  s21_size_t i = s21_strlen(str);
  if (c != '\0') {
    for (; i > 0; i--) {
      if (str[i] == c && flag == 0) {
        arc = (char *)&str[i];
        flag = 1;
      }
    }
  } else {
    arc = (char *)&str[i];
  }
  return arc;
}