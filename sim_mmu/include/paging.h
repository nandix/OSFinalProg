#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#ifndef _PAGING_H_
#define _PAGING_H_

//Paging Functions
void paging(void);
void page_table_sizes( int ** page_table, int *pages, int **frame_table, int *frames, int *pages_size );
void paging_algorithm( int *page_table, int* pages, int *frame_table, int *frames, int *page_size, int *p, int *d);
void access_physical_mem( const int *d, const int *frame, const int *frames, const int *page);
#endif

