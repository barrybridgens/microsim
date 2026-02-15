/* microsim_registers.h */

#ifndef _MICROSIM_REGISTERS_H
#define _MICROSIM_REGISTERS_H

#include "microsim_types.h"

u8 acc;
u16 pc;
u16 sp;
u16 ix;
u8 flags;

u8 char_out;

/* Flag bit patterns */
#define ZERO_FLAG 1

#endif
