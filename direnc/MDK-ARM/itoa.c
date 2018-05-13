#include "itoa.h"
char *itoa (int __val, char *__s, int __radix)
{
    if (!__builtin_constant_p (__radix)) {
    extern char *__itoa (int, char *, int);
    return __itoa (__val, __s, __radix);
    } else if (__radix < 2 || __radix > 36) {
    *__s = 0;
    return __s;
    } else {
    extern char *__itoa_ncheck (int, char *, unsigned char);
    return __itoa_ncheck (__val, __s, __radix);
    }
}