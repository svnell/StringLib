#include "s21_string.h"

int s21_strcmp(const char *str1, const char *str2) {
  int value = 0, flag = 1;
  unsigned char *ustr1 = (unsigned char *)str1;
  unsigned char *ustr2 = (unsigned char *)str2;
  for (s21_size_t i = 0; (ustr1[i] || ustr2[i]) && flag; i++) {
    if (ustr1[i] != ustr2[i]) {
      value = ustr1[i] - ustr2[i];
      flag = 0;
    }
  }
  return value;
}