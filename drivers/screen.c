#include "../kernel/ports.h"
#include "../drivers/screen.h"
#include "../libc/mem.h"
#include <stdarg.h> 
/*-------------------------------------------
These are the public functions for the class
-------------------------------------------*/
void move_cur(int col, int row) {set_cur(get_screen_offset(col,row));}
int cur_row(int offset){return offset / (2 * MAX_COLS);}
int cur_col(int offset){return (offset - (cur_row(offset)*2*MAX_COLS))/2;} 

void print(volatile unsigned char *msg, char att, int count, ...) 
{
	va_list args;
   va_start(args,count);
   for(int i = 0; msg[i] != 0; i++) 
   { 
   	
   	if(msg[i] == '%')
   	{
   		i++;
   		if(msg[i] == 'd')
   		{
   			unsigned char *var = va_arg(args, char*);
   			for (int j = 0; var[j] != 0; j++)
   			{
   				print_char(var[j], -1,-1,att);
   			}
   			i++;
   		}
   	}
     	print_char(msg[i], -1, -1, att);
   }
   va_end(args);
}

void fill_screen(char c)
{
	int count = MAX_COLS * MAX_ROWS;
	for(int i = 0; i<count; i++) 
   {
     	print_char(c, -1, -1, WHITE_ON_BLACK);
   }
}

void clear_screen()
{
	int row = 0;
	int col = 0;

	for(row = 0; row<MAX_ROWS; row++)
	{
		for(col = 0; col<MAX_COLS; col++)
		{
			print_char(' ', col, row, WHITE_ON_BLACK);
		}
	}
	set_cur(get_screen_offset(0,0));
}

/*-------------------------------------------
These are the private functions for the class
-------------------------------------------*/
int get_screen_offset(int col, int row) {return (row * MAX_COLS + col) *2;}

void print_char(volatile unsigned char c, int col, int row, char att)
{
	int offset;

	if(col <0 && row <0)
	{
		offset = get_cur();
	}
	else
	{
		offset = get_screen_offset(col,row);
	}
	offset =scroll_screen(offset);

	if(c == '\n')
	{
		move_cur(79, (cur_row(offset)));
		offset = get_cur();
	}
	else
	{
	unsigned short *mem_print_loc;
	mem_print_loc = (unsigned short*)VIDEO_ADDRESS + (offset/2) ;
	*mem_print_loc = c | (att << 8);		
	}

	
	
	offset += 2;
	set_cur(offset);
}

int get_cur()
{
	port_outb(REG_SCREEN_CTRL, 14);
	int offset = port_inb(REG_SCREEN_DATA) << 8;
	port_outb(REG_SCREEN_CTRL, 15);
	offset += port_inb(REG_SCREEN_DATA);
	return offset * 2;
}

void set_cur(int offset)
{
	offset /= 2;
	port_outb(REG_SCREEN_CTRL, 14);
	port_outb(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
	port_outb(REG_SCREEN_CTRL, 15);
	port_outb(REG_SCREEN_DATA, (unsigned char)(offset));
}

int scroll_screen(int offset)
{
	if (cur_row(offset) <MAX_ROWS-1){return offset;}

	memcpy((void*) (VIDEO_ADDRESS+(MAX_COLS*2)),VIDEO_ADDRESS, 24*MAX_COLS*2);
	memset(0 ,(void*)(VIDEO_ADDRESS+(24*MAX_COLS*2)), MAX_COLS);

	set_cur(get_cur()-(MAX_COLS*2));
	offset = get_cur();
	return offset;
}






