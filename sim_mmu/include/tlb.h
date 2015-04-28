#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#ifndef _TLB_H_

#define _TLB_H_
void tlb(void);
void set_up_tlb();
int tlb_replacement( );
void tlb_set_up( int **tlb_pages, int *num_tlb, int *iterations, int **frames, int *pages );
bool in_tlb( const int *tlb_pages, const int *frames, const int *num_tlb, const int *page, int *frame_num );
void tlb_miss_random(int *tlb_pages, int* pages, int* max_tlb, int* max_pages);
void tlb_miss_round_robin( int *tlb_pages, int* pages, int* max_tlb, int* max_pages);
void tlb_miss_least_used( int *tlb_pages, int* pages, int* max_tlb, int *max_pages);

#endif
