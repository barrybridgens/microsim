/* Microsim - main file */

#include <stdio.h>

#include "microsim_memory.h"
#include "microsim_registers.h"
#include "microsim_op-codes.h"

#define DEBUG 1

// memory_cell m[MEMORY_SIZE];

int main(void);
void init(void);
void show_registers(void);
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
}

void show_registers()
{
	printf("    acc = %d\n", acc);
	printf("    pc = %d\n", pc);
}

void load_code()
{
	m[0x100] = LDA_I;
	m[0x101] = 0x55;
	m[0x102] = HALT;
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
				printf ("LDA_I %d\n", data);
				#endif
				break;

			case HALT:
				#ifdef DEBUG
				printf("*** HALT ***\n");
				#endif
				break;

			//dafault:
				/* Do nothing for now */
		}

		#ifdef DEBUG
		show_registers();
		#endif
	}
}