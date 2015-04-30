
#ifndef _PAGING_H_
#include "../include/paging.h"
#endif

#ifndef _PAGING_ALG_H_
#include "../include/paging_algorithms.h"
#endif

void fifo_alg(void){
    //Create table to simulate frames
    page *frame_table;
    // Create table to simulate list lookup
    page *page_list;
    //number of pages/frames
    int pages, frames;
    int page_requests;

    //number of simulations to run
    int iterations;
    int p, d, i;

    //Generate a mock frame table, list of pages, list of pages to be requested
    create_frame_table( &frame_table, &frames );

    create_page_list( &frames, &page_list, &pages, &page_requests );

    for( i = 0; i < page_requests; i++ )
    {
        // Run page replacement algorithm selected type
        continue;
    }

    free(page_list);
    free(frame_table);

}


void optimal_alg(void){
	return;
}

void lru_alg(void){
	return;
}