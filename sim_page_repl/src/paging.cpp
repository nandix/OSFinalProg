#include "../include/paging.h"



void create_frame_table( page **frame_table, int *frames )
{
    int count, tmp, i;
    do
    {
        printf("How many frames are to be implemented (>4): ");
        scanf("%d", frames);
    }while(*frames < 4);
    
    *frame_table = (page*)malloc( sizeof(page) * (*frames));
    
    // Mark all frames as empty
    for( i = 0; i < *frames; i++ ){
        page temp;
        temp.page_num = -1;
        temp.frame_num = i;
        (*frame_table)[i] = temp;
    }
}

void create_page_list( int *frames, page **page_list, int *pages, int *page_requests ){

    int count, tmp, i;
    do
    {
        printf("How many different pages are to be implemented (>%d): ", *frames);
        scanf("%d", pages);

        printf("How many page requests would you like to simulate (>%d): ", *frames);
        scanf("%d", page_requests );

    }while(*pages < *frames || *page_requests < *frames);

    *page_list = (page*)malloc( sizeof(page) * (*page_requests));

    // Generate a list of random page requests
    for( i = 0; i < *page_requests; i++ ){
        page temp;
        temp.page_num = rand() % *pages;
        temp.frame_num = -1;
        (*page_list)[i] = temp;
    }
}
/*
void paging_algorithm( int *page_table, int * pages, int *frame_table, int *frames, int *page_size, int *p, int *d )
{
    int i;
    bool found = false;

    printf( "Looking for %d in page table:\n", *p);
    for( i = 0; i < *pages && !found; i++)
    {
        if( i == *p )
        {
            found = true;
            printf("Entry found in page %d.\nAccessing frame %d with offset of %d bytes\n", i, page_table[i], *d);
            access_physical_mem( d, &page_table[i], frames, page_size);
        }
    }
    if(!found)
        printf("Entry not found in page table. Tried accessing %d.\n\n", *p);
}
*/