#include "../cpu/paging.h"
#include "../drivers/screen.h"

void pagefile_init()
{
	print("\ninitializing paging file...\n", WHITE_ON_BLACK,0);
	unsigned int page_directory[1024] __attribute__((aligned(4096)));
	unsigned int page_table[1024] __attribute__((aligned(4096)));

	int i;
	for(i=0; i<1024; i++)
	{
		page_directory[i] = 0x00000002;
		page_table[i]= (i* 0x1000) | 3;
	}	

	page_directory[0] = ((unsigned int)page_table) | 3;
	
	load_page_directory(page_directory);
	enable_paging();
	print("successfully enabled paging file \n", WHITE_ON_BLACK,0);
}

