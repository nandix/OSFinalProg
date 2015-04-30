#include "../include/paging.h"

void paging(void)
{
    //page and frame table arrays
    page *page_table;
    page *frame_table;
    //number of pages/frames
    int pages, frames;

    //number of simulations to run
    int iterations;
    int p, d, i;
    create_page_table( &page_table, &pages, &frame_table, &frames );
    
    printf("How many page requests to run: ");
    scanf("%d", &iterations );
    printf("\n");

    // Generate a list of pages of size 'iterations'

    for( i = 0; i < iterations; i++ )
    {
        // Run page replacement algorithm selected type
        continue;
    }

    free(page_table);
    free(frame_table);

}

void create_page_table( page **page_table, int *pages, page **frame_table, int *frames )
{
    int count, tmp, i;
    do
    {
        printf("How many frames are to be implemented: ");
        scanf("%d", frames);
        printf("How many pages are to be implemented (<= frames): ");
        scanf("%d", pages);
        if( *frames < *pages )
            printf( "Number of pages must be greater than or equal to frames to simulate 
                    page replacement.\n");
    }while(*frames < *pages);
    
    *frame_table = (page*)malloc( sizeof(page) * (*frames));
    *page_table = (page*)malloc( sizeof(page) *  (*pages) );
    
    for( i = 0; i < *frames; i++ )
        (*frame_table)[i] = -1;
    tmp = rand() % *frames;
    
    for( i = 0; i < *pages; i++ )
    {
        while( (*frame_table)[tmp] != -1 ) 
            tmp = rand() % *frames;
        (*page_table)[i] = tmp;
        (*frame_table)[tmp] = i;
    }
    printf("Page table contains:\n");
    for( i = 0; i < *pages; i++)
        printf("Entry %d refrences %d frame in physical memory\n",i,(*page_table)[i]);
    printf("\n");
}

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

void access_physical_mem( const int *d, const int *frame, const int *frames, const int *page_size)
{
    int tmp, total_mem;
    //sleep for 1 second to simulate access time to physical memory
    sleep(1);
    if( *d < *page_size)
        printf("Frame, %d, with offset, %d, accessed successfully.\n\n", *frame, *d);
    else
    {
        tmp = (*frame) * (*page_size) + *d;
        total_mem = (*frames) * (*page_size);
        if( tmp >= total_mem )
            printf("The offset, %d, accessed non existent memory.\n\n", *d);
        else
            printf("The offset, %d, accessed frame, %d, which is not associated with original look up.\n\n", *d, tmp/ (*frames)  );
    }
}
