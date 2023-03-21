#include "s21_string.h"

void *s21_to_lower(const char *str) {
  char *ch = s21_NULL;
  if (str) {
    ch = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (ch) {
      s21_strcpy(ch, str);
      for (s21_size_t i = 0; i < s21_strlen(str); i++) {
        if (ch[i] >= 'A' && ch[i] <= 'Z') ch[i] += 32;
      }
    }
  }

  return (ch);
}