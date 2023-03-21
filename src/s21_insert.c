#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *ch_insert = s21_NULL;

  if (s21_strlen(src) >= start_index && src) {
    ch_insert =
        (char *)calloc((s21_strlen(src) + s21_strlen(str) + 1), sizeof(char));
    if (ch_insert) {
      s21_size_t i = 0;
      s21_size_t j = 0;
      for (; i < start_index; i++) {
        ch_insert[i] = src[i];
      }
      for (; j < s21_strlen(str); j++) {
        ch_insert[i + j] = str[j];
      }
      for (i = start_index; i < s21_strlen(src); i++) {
        ch_insert[i + j] = src[i];
      }
    }
  }
  return ch_insert;
}