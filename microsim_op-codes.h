/* Microsim - op-code definitions */

#ifndef _MICROSIM_OP_CODES
#define _MICROSIM_OP_CODES

#define LDA_I    0x01   /* Load accumulator immediate - data: value to load */
#define LDA_M    0x02   /* Load accumulator from memory - data: memory address high, memory address low */
#define STA      0x03   /* Store accumulator to memory - data: memory address high, memory address low */
#define ADD_I    0x04   /* Add immediate - data: value to add to accumulator */
#define ADD_M    0x05   /* Add from memory - data: memory address high, memory address low */
#define INC      0x06   /* Increment accumulator */
#define DEC      0x07   /* Decrement accumulator */
#define BRNZ     0x08   /* Branch if not zero - data: data: memory addredata: memory offset high, memory offset low */
#define OUT      0x09   /* Out the value in accumulator ie. store it in the char_out register */
#define JMP      0x0A   /* Set program counter to the given address - data: memory address high, memory address low */
#define JSR      0x0B   /* Push PC to stack, set program counter to the given address - data: memory address high, memory address low */
#define RET      0x0C   /* Pull value from stack, put value into PC */
#define LDI_I    0x0D   /* Load an immediate value into the index register - data: value high, value low */
#define LDI_M    0x0E   /* Load the index register from a memory location - data: memory address high, memory address low */
#define INCI     0x0F   /* Increment index register */
#define DECI     0x10   /* Decrement index register */
#define LDAI     0x11   /* Load accumulator from address in index register */
#define LDAIO    0x12   /* Load accumulator from address in index register plus an offset data: offset */
#define STAI     0x13   /* Store accumulator at address in index register */
#define STAIO    0x14   /* Store accumulator at address in index register plus an offset data: offset */

#define HALT     0xFF  /* Stop execution */


#endif
