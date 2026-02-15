/* Microsim - main file */

#include <ctype.h>
#include <stdio.h>
#include <unistd.h>

#include "microsim_memory.h"
#include "microsim_registers.h"
#include "microsim_op-codes.h"

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

#define DEBUG 1

// memory_cell m[MEMORY_SIZE];
#define OUTPUT_BUFFER_SIZE 20
char output_buffer[OUTPUT_BUFFER_SIZE];
int output_buffer_position = 0;

int main(void);
void init(void);
void show_registers(void);
void show_memory(u16 addr);
void load_code(void);
void fetch_and_execute(void);
void set_flags(u8 old_value, u8 new_value);
void perform_io(void);



int main()
{
  printf("Microsim v0.1\n\n");

  init();

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
  ix = 0;

  char_out = 0xFF;
}

void show_registers()
{
  gotoxy(80, 3);
  printf("acc = %x\n", acc);
  gotoxy(80, 4);
  printf("pc = %x\n", pc);
  gotoxy(80, 5);
  printf("ix = %x\n", ix);
  gotoxy(80, 6);
  printf("sp = %x\n", sp);
  if (sp != 0xFFFE)
  {
    gotoxy(80, 7);
    printf("     %x\n", m[sp+1]);
    gotoxy(80, 8);
    printf("     %x\n", m[sp+2]);
  }
  gotoxy(80, 10);
  printf("flags = %x\n", flags);
  gotoxy(80, 12);
  printf("char_out = %x\n", char_out);
}

void show_memory (u16 addr)
{
  u8 data[16];

  gotoxy(1, 4);
  
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
  int load_addr;
  int  data;

  FILE *fptr;

  // Open obj file in read mode
  fptr = fopen("test.obj", "r");

  // Store the content of the file
  char myString[100];

  // Read the content and print it
  while(fgets(myString, 100, fptr)) {
    printf("%s", myString);
    sscanf(myString, "%d %d", &load_addr, &data);
    m[load_addr] = data;
  }


  // Close the file
  fclose(fptr); 

  

  /* load test data */
  /*m[0x10] = 0x40;
  m[0x11] = 0x33;
  m[0x14] = 0x42;
  m[0x20] = 0x00;
  m[0x21] = 0x30;*/

  /* load test code */
  /*m[load_addr++] = LDA_I;
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
    m[load_addr++] = LDA_I;
    m[load_addr++] = 0x00;*/

  /* index register tests */

  /*m[load_addr++] = LDI_I;
  m[load_addr++] = 0x00;
  m[load_addr++] = 0x10;
  m[load_addr++] = LDAI;
  m[load_addr++] = INCI;
  m[load_addr++] = LDAI;
  m[load_addr++] = INCI;
  m[load_addr++] = STAI;
  m[load_addr++] = DECI;
  m[load_addr++] = LDAIO;
  m[load_addr++] = 0x03;
  m[load_addr++] = STAIO;
  m[load_addr++] = 0x05;
  m[load_addr++] = LDI_M;
  m[load_addr++] = 0x00;
  m[load_addr++] = 0x20;
  

  m[load_addr++] = HALT;*/

  /* JMP test */
  /*m[load_addr++] = JMP;
  m[load_addr++] = 0x01;
  m[load_addr++] = 0x09;*/

  /* Loop test */
  /*m[load_addr++] = LDA_I;
  m[load_addr++] = 0x04;
  m[load_addr++] = DEC;
  m[load_addr++] = BRNZ;
  m[load_addr++] = 0xFF;
  m[load_addr++] = 0xFF;*/

	
  /* IO test */
  /*m[load_addr++] = LDA_I; /* 109 */
  /*m[load_addr++] = 0x41;
  m[load_addr++] = OUT;
  m[load_addr++] = LDA_I;
  m[load_addr++] = 0x42;
  m[load_addr++] = OUT;
  m[load_addr++] = LDA_I;
  m[load_addr++] = 0x43;
  m[load_addr++] = OUT;*/

  /*m[load_addr++] = JSR; /* 112 */
  /*m[load_addr++] = 0x01;
  m[load_addr++] = 0x16;

  m[load_addr++] = HALT; */

  /* Sub routine */
  /*m[load_addr++] = LDA_I; /* 116 */
  /*m[load_addr++] = 0x45;
  m[load_addr++] = OUT;
  m[load_addr++] = LDA_I;
  m[load_addr++] = 0x46;
  m[load_addr++] = OUT;
  m[load_addr++] = LDA_I;
  m[load_addr++] = 0x47;
  m[load_addr++] = OUT;
  m[load_addr++] = RET;*/

  
}

void set_flags(u8 old_value, u8 new_value)
{
  /* Zero Flag */
  if (new_value == 0)
  {
    flags = flags | ZERO_FLAG;
  }
  else
  {
    flags = flags & ~ZERO_FLAG;
  }
}

void perform_io()
{
  /* Simulate IO */
  if (char_out != 0xFF)
  {
    if (output_buffer_position < OUTPUT_BUFFER_SIZE)
    {
      output_buffer[output_buffer_position] = char_out;
      output_buffer_position++;
    }
    // putchar((char)char_out);
    char_out = 0xFF;
  }
  gotoxy(80, 14);
  printf(output_buffer);
}

void fetch_and_execute()
{
  u8 op;
  u8 data;
  u16 data16;
  u16 addr;
  u8 old_acc;

  u8 single_step = 1;
  char command;

  op = 0;

  while (op != HALT)
  {
    clear();
    
    op = m[pc++];

    switch (op)
    {
    case LDA_I:
      old_acc = acc;
      data = m[pc++];
      acc = data;
      set_flags(old_acc, acc);
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("LDA_I %x\n", data);
#endif
      break;

    case LDA_M:
      old_acc = acc;
      addr = (m[pc++] * 256) + m[pc++];
      acc = m[addr];
      set_flags(old_acc, acc);
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("LDA_M %x\n", addr);
#endif
      break;

    case STA:
      old_acc = acc;
      addr = (m[pc++] * 256) + m[pc++];
      m[addr] = acc;
      set_flags(old_acc, acc);
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("STA %x\n", addr);
#endif
      break;

    case ADD_I:
      old_acc = acc;
      data = m[pc++];
      acc = acc + data;
      set_flags(old_acc, acc);
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("ADD_I %x\n", data);
#endif
      break;

    case ADD_M:
      old_acc = acc;
      addr = (m[pc++] * 256) + m[pc++];
      acc = acc + m[addr];
      set_flags(old_acc, acc);
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("ADD_M %x\n", addr);
#endif
      break;

    case INC:
      old_acc = acc;
      acc++;
      set_flags(old_acc, acc);
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("INC\n");
#endif
      break;

    case DEC:
      old_acc = acc;
      acc--;
      set_flags(old_acc, acc);
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("DEC\n");
#endif
      break;

    case BRNZ:
      addr = (m[pc++] * 256) + m[pc++];
      if ((flags & ZERO_FLAG) != ZERO_FLAG)
      {
	pc = addr;
      }
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("BRNZ %x\n", addr);
#endif
      break;

    case OUT:
      char_out = acc;
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("OUT\n");
#endif
      break;

    case JMP:
      addr = (m[pc++] * 256) + m[pc++];
      pc = addr;
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("JMP %x\n", addr);
#endif
      break;

    case JSR:
      addr = (m[pc++] * 256) + m[pc++];
      m[sp--] = pc / 256;
      m[sp--] = pc & 0xFF;
      pc = addr;
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("JSR %x\n", addr);
#endif
      break;

    case RET:
      addr = m[++sp];
      addr = addr + (m[++sp] * 256);
      pc = addr;
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("RET\n");
#endif
      break;
				
    case LDI_I:
      data16 = (m[pc++] * 256);
      data16 = data16 + m[pc++];
      ix = data16;
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("LDI_I %x\n", data16);
#endif
      break;

    case LDI_M:
      addr = (m[pc++] * 256) + m[pc++];
      printf("xxxxx Address: %x\n", addr);
      data16 = (m[addr] * 256);
      data16 = data16 + m[addr + 1];
      printf("xxxxx Data: %x\n", data16);
      ix = data16;
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("LDI_M - %x\n", addr);
#endif
      break;

    case INCI:
      ix++;
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("INCI\n");
#endif
      break;

    case DECI:
      ix--;
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("DECI\n");
#endif
      break;

    case LDAI:
      old_acc = acc;
      acc = m[ix];
      set_flags(old_acc, acc);
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("LDAI\n");
#endif
      break;

    case LDAIO:
      data = m[pc++];
      old_acc = acc;
      acc = m[ix + data];
      set_flags(old_acc, acc);
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("LDAI\n");
#endif
      break;
      
    case STAI:
      old_acc = acc;
      addr = ix;
      m[addr] = acc;
      set_flags(old_acc, acc);
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("STAI \n");
#endif
      break;

    case STAIO:
      data = m[pc++];
      old_acc = acc;
      addr = ix + data;
      m[addr] = acc;
      set_flags(old_acc, acc);
#ifdef DEBUG
      gotoxy(80, 12);
      printf ("STAI \n");
#endif
      break;
      
    case HALT:
#ifdef DEBUG
      gotoxy(80, 12);
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

    perform_io();

    if (single_step == 1)
    {
      //scanf(" %c", &command);
      command = getchar();
      if (command == 'r')
      {
	single_step = 0;
      }
    }
  }
}
