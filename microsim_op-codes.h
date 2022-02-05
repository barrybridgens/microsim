/* Microsim - op-code definitions */

#ifndef _MICROSIM_OP_CODES
#define _MICROSIM_OP_CODES

#define LDA_I    1   /* Load accumulator immediate - data: value to load */
#define LDA_M    2   /* Load accumulator from memory - data: memory address high, memory address low */
#define STA      3   /* Store accumulator to memory - data: memory address high, memory address low */
#define ADD_I    4   /* Add immediate - data: value to add to accumulator */
#define ADD_M    5   /* Add from memory - data: memory address high, memory address low */
#define INC      6   /* Increment accumulator */
#define DEC      7   /* Decrement accumulator */
#define BRNZ     8   /* Branch is not zero - data: data: memory addredata: memory offset high, memory offset low */
#define OUT      9   /* Out the value in accumulator ie. store it in the char_out register */

#define HALT    255  /* Stop execution */


#endif
