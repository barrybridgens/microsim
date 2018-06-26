/* Microsim - main file */

#include <stdio.h>

#include "microsim_memory.h"

memory_cell m[MEMORY_SIZE];

int main(void);
void init(void);

int main()
{
	printf("Microsim v0.1\n\n");

	init();

	return(1);
}

void init()
{
	/* Zero all memory */
	for (u32 cell=0; cell<MEMORY_SIZE; cell++)
	{
		m[cell] = 0;
	}
}
