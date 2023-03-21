#include <math.h>

#include "s21_sscanf.h"

int s21_atoii(const char *str) {
  int atoint = 0;
  int sign = 1;  //если подают отрицательное число
  if (*str == '-' && *(str + 1) != '+') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    sign = 1;
    str++;
  }
  while (*str && *str >= '0' && *str <= '9') {
    atoint = atoint * 10 + (*str - '0');
    str++;
  }
  if (sign < 0) atoint *= sign;
  return (atoint);
}

long s21_atol(const char *str) {
  long atol = 0;
  int sign = 1;  //если подают отрицательное число

  if (*str == '-' && *(str + 1) != '+') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    sign = 1;
    str++;
  }
  while (*str && *str >= '0' && *str <= '9') {
    atol = atol * 10 + (*str - '0');
    str++;
  }
  if (sign < 0) atol *= sign;
  return (atol);
}

long long s21_atoll(const char *str) {
  long long atol = 0;
  int sign = 1;  //если подают отрицательное число
  // int zero = 0;

  //   while (*str != ' ') {
  //   }
  if (*str == '-' && *(str + 1) != '+') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    sign = 1;
    str++;
  }
  while (*str && *str >= '0' && *str <= '9') {
    atol = atol * 10 + (*str - '0');
    str++;
  }
  if (sign < 0) atol *= sign;
  return (atol);
}

short s21_atos(const char *str) {
  short atos = 0;
  int sign = 1;  //если подают отрицательное число
  if (*str == '-' && *(str + 1) != '+') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    sign = 1;
    str++;
  }
  while (*str && *str >= '0' && *str <= '9') {
    atos = atos * 10 + (*str - '0');
    str++;
  }
  if (sign < 0) atos *= sign;
  //   if (atoint >)
  return (atos);
}

float s21_atof(const char *str) {
  float atof = 0;
  float fraction = 0;
  int n = 0;  //кол-во знаков после запятой
  int sign = 1;
  if (*str == '-' && *(str + 1) != '+') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  while (*str && ((*str >= '0' && *str <= '9') || *str == '.')) {
    if (*str == '.') {
      str++;
      break;
    }

    atof = atof * 10 + (*str - '0');
    str++;
  }
  //   printf("%f\n", atof);
  while (*str && *str >= '0' && *str <= '9' && n != 5) {
    n++;
    fraction = (*str - '0');
    atof = atof + (fraction / pow(10, n));
    str++;
    // printf("%f\n", fraction / pow(10, n));
  }
  //   atof += (fraction / n);
  if (sign < 0) atof *= sign;
  return (atof);
}

double s21_atod(const char *str) {
  double atod = 0;
  double fraction = 0;
  int n = 0;  //кол-во знаков после запятой
  int sign = 1;
  if (*str == '-' && *(str + 1) != '+') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  while (*str && ((*str >= '0' && *str <= '9') || *str == '.')) {
    if (*str == '.') {
      str++;
      break;
    }

    atod = atod * 10 + (*str - '0');
    str++;
  }
  while (*str && *str >= '0' && *str <= '9') {
    n++;
    fraction = (*str - '0');
    atod = atod + (fraction / pow(10, n));
    str++;
    // printf("%f\n", fraction / pow(10, n));
  }
  if (sign < 0) atod *= sign;
  return (atod);
}

long double s21_atold(const char *str) {
  long double atold = 0;
  long double fraction = 0;
  int n = 0;  //кол-во знаков после запятой
  int sign = 1;
  if (*str == '-' && *(str + 1) != '+') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  while (*str && ((*str >= '0' && *str <= '9') || *str == '.')) {
    if (*str == '.') {
      str++;
      break;
    }
    atold = atold * 10 + (*str - '0');
    str++;
  }
  while (*str && *str >= '0' && *str <= '9') {
    n++;
    fraction = (*str - '0');
    atold = atold + (fraction / pow(10, n));
    str++;
    // printf("%Lf\n", fraction / pow(10, n));
  }
  if (sign < 0) atold *= sign;
  return (atold);
}

long s21_atohex(const char *str) {
  long hex = 0;
  int degree = 0;
  int sign = 1;
  int short_pow = 0;
  if (*str == '-' && *(str + 1) != '+') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    str += 2;
  }
  degree = s21_strlen(str) - 1;
  while (*str &&
         ((*str >= '0' && *str <= '9') ||
          ((*str >= 'a' && *str <= 'f') || (*str >= 'A' && *str <= 'F'))) &&
         degree >= 0) {
    short_pow = (int)pow(16, degree);
    if (*str == 'a' || *str == 'A') {
      hex = hex + (10 * short_pow);
    } else if (*str == 'b' || *str == 'B') {
      hex = hex + (11 * short_pow);
    } else if (*str == 'c' || *str == 'C') {
      hex = hex + (12 * short_pow);
    } else if (*str == 'd' || *str == 'D') {
      hex = hex + (13 * short_pow);
    } else if (*str == 'e' || *str == 'E') {
      hex = hex + (14 * short_pow);
    } else if (*str == 'f' || *str == 'F') {
      hex = hex + (15 * short_pow);
    } else {
      hex = hex + ((*str - '0') * short_pow);
    }
    degree--;
    str++;
  }
  if (sign < 0) hex *= sign;
  return hex;
}

long s21_ato8(const char *str) {
  long hex = 0;
  int degree = 0;
  int sign = 1;
  int short_pow = 0;
  if (*str == '-' && *(str + 1) != '+') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  degree = s21_strlen(str) - 1;
  while (*str && (*str >= '0' && *str <= '7') && degree >= 0) {
    short_pow = (int)pow(8, degree);
    hex = hex + ((*str - '0') * short_pow);
    degree--;
    str++;
  }
  if (sign < 0) hex *= sign;
  return hex;
}

long double s21_atoE(const char *str) {
  long double atold = 0;
  long double fraction = 0;
  int n = 0;  //кол-во знаков после запятой
  int sign = 1;
  int degree = 0;
  int sign_degree = 1;
  int e = 0;
  if (*str == '-' && *(str + 1) != '+') {
    sign = -1;
    str++;
  } else if (*str == '+') {
    str++;
  }
  while (*str && ((*str >= '0' && *str <= '9') || *str == '.')) {
    if (*str == '.') {
      str++;
      break;
    }
    atold = atold * 10 + (*str - '0');
    str++;
  }
  while (*str &&
         ((*str >= '0' && *str <= '9') || (*str == 'e') || (*str == 'E')) &&
         e == 0) {
    if (*str == 'e' || *str == 'E') {
      // printf("atold %f\n", atold);
      e = 1;
      str++;
    } else {
      n++;
      fraction = (*str - '0');
      atold = atold + (fraction / pow(10, n));
      str++;
    }
  }
  if (*str == '-' && *(str + 1) != '+') {
    sign_degree = -1;
    str++;
  }
  if (*str == '+') {
    str++;
  }
  while (*str && *str >= '0' && *str <= '9') {
    // printf("%c", *str);
    degree = degree * 10 + (*str - '0');
    str++;
  }
  if (sign_degree < 0) degree *= sign_degree;
  // printf("\n");
  // printf("atold:%f degree:%d\n", atold, degree);
  atold = atold * pow(10, degree);
  if (sign < 0) atold *= sign;
  return (atold);
}

unsigned long s21_usigned_atohex(const char *str) {
  unsigned long hex = 0;
  int degree = 0;
  int sign = 1;
  int short_pow = 0;
  if (*str == '0' && (*(str + 1) == 'x' || *(str + 1) == 'X')) {
    str += 2;
  }
  degree = s21_strlen(str) - 1;
  while (*str &&
         ((*str >= '0' && *str <= '9') ||
          ((*str >= 'a' && *str <= 'f') || (*str >= 'A' && *str <= 'F'))) &&
         degree >= 0) {
    short_pow = (int)pow(16, degree);
    if (*str == 'a' || *str == 'A') {
      hex = hex + (10 * short_pow);
    } else if (*str == 'b' || *str == 'B') {
      hex = hex + (11 * short_pow);
    } else if (*str == 'c' || *str == 'C') {
      hex = hex + (12 * short_pow);
    } else if (*str == 'd' || *str == 'D') {
      hex = hex + (13 * short_pow);
    } else if (*str == 'e' || *str == 'E') {
      hex = hex + (14 * short_pow);
    } else if (*str == 'f' || *str == 'F') {
      hex = hex + (15 * short_pow);
    } else {
      hex = hex + ((*str - '0') * short_pow);
    }
    degree--;
    str++;
  }
  if (sign < 0) hex *= sign;
  return hex;
}

unsigned long s21_unsigned_ato8(const char *str) {
  unsigned long hex = 0;
  int degree = 0;
  int sign = 1;
  int short_pow = 0;
  degree = s21_strlen(str) - 1;
  while (*str && (*str >= '0' && *str <= '7') && degree >= 0) {
    short_pow = (int)pow(8, degree);
    hex = hex + ((*str - '0') * short_pow);
    degree--;
    str++;
  }
  if (sign < 0) hex *= sign;
  return hex;
}
