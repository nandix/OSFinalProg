#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#ifndef _TLB_H_

#define _TLB_H_
void tlb(void);
void tlb_set_up( int **tlb_pages, int **tlb_frames, int *num_tlb, *page_table, int *pages);
int tlb_replacement( );
bool in_tlb( const int *tlb_pages, const int *tlb_frames, const int *num_tlb, const int *page_size, const int *frames, const int *p, const int *d);
void tlb_miss_random( int *tlb_pages, int *tlb_frames, int* pages, int* max_tlb, int* max_pages );
void tlb_miss_round_robin( int *tlb_pages, int *tlb_frames, int* pages, int* max_tlb, int* max_pages );
void tlb_miss_least_used( int *tlb_pages, int *tlb_frames, int* pages, int* max_tlb, int *max_pages );
#endif
