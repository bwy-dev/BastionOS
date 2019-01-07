#ifndef PAGING_H
#define PAGING_H

extern void load_page_directory(unsigned int*);
extern void enable_paging();

void pagefile_init();

#endif