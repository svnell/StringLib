#define s21_NULL ((void *)0)
typedef long unsigned s21_size_t;

#include <stdio.h>
#include <stdlib.h>

s21_size_t s21_strlen(const char *str);
void *s21_memset(void *str, int c, s21_size_t n);
char *s21_strcat(char *dest, const char *src);
char *s21_strncat(char *dest, const char *src, s21_size_t n);
void *s21_memchr(const void *str, int c, s21_size_t n);
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
void *s21_memmove(void *dest, const void *src, s21_size_t n);
char *s21_strpbrk(const char *str1, const char *str2);
int s21_strcmp(const char *str1, const char *str2);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
s21_size_t s21_strcspn(const char *str1, const char *str2);
char *s21_strchr(const char *str, int c);
char *s21_strcpy(char *dest, const char *src);
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
char *s21_strerror(int errnum);
char *s21_strrchr(const char *str, int c);
s21_size_t s21_strspn(const char *str1, const char *str2);
char *s21_strstr(const char *str, const char *needle);

char *s21_strtok(char *s, const char *delim);
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
void *s21_trim(const char *src, const char *trim_chars);
void *s21_to_lower(const char *str);
void *s21_to_upper(const char *str);

int s21_sprintf(char *str, const char *format, ...);
int s21_sscanf(const char *str, const char *format, ...);

int s21_atoii(const char *str);
long s21_atol(const char *str);
long long s21_atoll(const char *str);
short s21_atos(const char *str);
float s21_atof(const char *str);
double s21_atod(const char *str);
long double s21_atold(const char *str);
long s21_atohex(const char *str);
unsigned long s21_usigned_atohex(const char *str);
long s21_ato8(const char *str);
unsigned long s21_unsigned_ato8(const char *str);
long double s21_atoE(const char *str);
