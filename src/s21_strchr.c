#include "s21_string.h"

char *s21_strchr(const char *str, int c) {
  char *arc = s21_NULL;
  int flag = 0;
  s21_size_t l = s21_strlen(str);
  for (s21_size_t i = 0; i < l; i++) {
    if (str[i] == c && flag == 0) {
      arc = (char *)&str[i];
      flag = 1;
    }
  }
  return arc;
}