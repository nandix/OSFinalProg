#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#ifndef _PAGING_H_
#define _PAGING_H_

//Paging Functions
void paging(void);
void set_up_page();
void page_table_sizes( int *pages, int *page_size, int** page_table );
void paging_algorithm( int *pages, int *page_size, int *page_table, int *page, int *frame );

#endif

