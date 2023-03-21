#include "s21_string.h"

s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t strs = 0;
  for (s21_size_t i = 0; i < s21_strlen(str1); i++) {
    int flag = 0;
    for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
      if (str1[i] == str2[j]) {
        strs++;
        flag = 1;
        break;
      }
    }
    if (!flag) break;
  }
  return strs;
}