#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

extern void hexDump(char *desc, void *addr, int len);

extern float next_float_val(bool reset);
extern bool gen_float_val(float* ret);

#endif // _COMMON_H_

