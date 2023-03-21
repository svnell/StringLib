#include <math.h>
#include <stdarg.h>

#include "s21_string.h"

#define HEX 16
#define DEC 10
#define OCT 8

typedef struct {
  int width;       // minimum number of character to be printed, -1 if not set
  int asterics;    // read but not assign
  char length;     // h, l or L
  char specifier;  // just specifier
  int error;
  int convertions;
} flags_t;

typedef struct {
  int sign_before_e;
  int sign_after_e;
  int dot;
  int e;
  int digit;
} float_flags_t;

// parse format string
void parseFormat(const char **format, flags_t *f);
const char *parseWidth(const char *format, flags_t *f);
const char *parseLength(const char *format, flags_t *f);
const char *parseSpecifier(const char *format, flags_t *f);

// parse input string
void parseString(const char **str, const s21_size_t str_len, flags_t *f,
                 va_list var, char skip);

// helper functions for parsing
int checkSign(const char *a, int *sign, int width, int base, int i);
int checkScience(const char *str, int width);
int checkString(const char *str);
int isSign(int a);
int isDigit(int a);
int isAscii(int a);
int isSeporator(int a);
int isHex(int a, int i);
int isOct(int a);
int isFloat(int a, int next, float_flags_t *fl);

// functions for assignment
void assignChar(char ch, va_list var, flags_t *f);
void assignString(char *str, va_list var, flags_t *f);
void assignFloat(char *str, va_list var, flags_t *f);
void assignN(int n, va_list var, flags_t *f);
void assignInt(char *str, va_list var, flags_t *f);
void assignHex(char *str, va_list var, flags_t *f);
void assignOct(char *str, va_list var, flags_t *f);
void assignIntUnsigned(char *str, va_list var, flags_t *f);
void assignOctUnsigned(char *str, va_list var, flags_t *f);
void assignHexUnsigned(char *str, va_list var, flags_t *f);
void assignVoid(char *str, va_list var, flags_t *f);
void assignScience(va_list var, flags_t *f, int flag);