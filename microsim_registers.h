/* microsim_registers.h */

#ifndef _MICROSIM_RIGISTERS_H
#define _MICROSIM_REGISTERS_H

#include "microsim_types.h"

u8 acc;
u16 pc;
u16 sp;
u16 index;
u8 flags;

/* Flag bit patterns */
#define ZERO_FLAG 1

#endif