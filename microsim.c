/* Microsim - main file */

#include <ctype.h>
#include <stdio.h>

#include "microsim_memory.h"
#include "microsim_registers.h"
#include "microsim_op-codes.h"

#define DEBUG 1

// memory_cell m[MEMORY_SIZE];

int main(void);
void init(void);
void show_registers(void);
void show_memory(u16 addr);
void load_code(void);
void fetch_and_execute(void);

int main()
{
	printf("Microsim v0.1\n\n");

	init();

	show_registers();

	load_code();

	fetch_and_execute();

	return(1);
}

void init()
{
	/* Zero all memory */
	for (u32 cell=0; cell<MEMORY_SIZE; cell++)
	{
		m[cell] = 0;
	}

	/* Initialise registers */
	acc = 0;
	pc = 0x100;
	sp = 0xFFFE;
}

void show_registers()
{
	printf("    acc = %x\n", acc);
	printf("    pc = %x\n", pc);
	printf("    sp = %x\n", sp);
}

void show_memory (u16 addr)
{
	u8 data[16];

	for (int byte=0; byte<16; byte++)
	{
		printf("%08x: ",(int)addr);

		for (int item=0; item<16; item++)
		{
			data[item] = m[addr];
			printf("%02X ", data[item]);
			addr++;
		}

		printf(" ");
		for (int item=0; item<16; item++)
		{
			if (isprint(data[item]))
			{
				printf("%c", data[item]);
			}
			else
			{
				printf(".");
			}
		}

		printf("\n");
	}
}

void load_code()
{
	u16 load_addr;

	load_addr = 0x100;

	/* load test data */
	m[0x10] = 0x40;
	m[0x11] = 0x33;

	/* load test code */
	m[load_addr++] = LDA_I;
	m[load_addr++] = 0x55;
	m[load_addr++] = LDA_M;
	m[load_addr++] = 0x00;
	m[load_addr++] = 0x10;
	m[load_addr++] = ADD_I;
	m[load_addr++] = 0x20;
	m[load_addr++] = ADD_M;
	m[load_addr++] = 0x00;
	m[load_addr++] = 0x11;
	m[load_addr++] = STA;
	m[load_addr++] = 0x00;
	m[load_addr++] = 0x14;
	m[load_addr++] = HALT;
}

void fetch_and_execute()
{
	u8 op;
	u8 data;
	u16 addr;

	op = 0;

	while (op != HALT)
	{
		op = m[pc++];

		switch (op)
		{
			case LDA_I:
				data = m[pc++];
				acc = data;
				#ifdef DEBUG
				printf ("LDA_I %x\n", data);
				#endif
				break;

			case LDA_M:
				addr = (m[pc++] * 256) + m[pc++];
				acc = m[addr];
				#ifdef DEBUG
				printf ("LDA_M %x\n", addr);
				#endif
				break;

			case STA:
				addr = (m[pc++] * 256) + m[pc++];
				m[addr] = acc;
				#ifdef DEBUG
				printf ("STA %x\n", addr);
				#endif
				break;

			case ADD_I:
				data = m[pc++];
				acc = acc + data;
				#ifdef DEBUG
				printf ("ADD_I %x\n", data);
				#endif
				break;

			case ADD_M:
				addr = (m[pc++] * 256) + m[pc++];
				acc = acc + m[addr];
				#ifdef DEBUG
				printf ("ADD_M %x\n", addr);
				#endif
				break;

			case HALT:
				#ifdef DEBUG
				printf("*** HALT ***\n");
				#endif
				break;

			default:
				/* Do nothing for now */
				break;
		}

		#ifdef DEBUG
		show_registers();
		show_memory(0);
		#endif
	}
}