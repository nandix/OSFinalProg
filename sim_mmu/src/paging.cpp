#include "../include/paging.h"

void paging(void)
{
    //page and frame table arrays
    int *page_table;
    int *frame_table;
    //number of pages/frames
    int pages, frames;
    //size of pages
    int page_size;
    //number of simulations to run
    int iterations;
    int p, d, i;
    page_table_sizes( &page_table, &pages, &frame_table, &frames, &page_size );
    
    printf("How many iterations to run: ");
    scanf("%d", &iterations );

    for( i = 0; i < iterations; i++ )
    {
        p = rand() % pages;
        d = rand() % (page_size * 2);
        paging_algorithm( page_table, &pages, frame_table,  &frames, &page_size, &p, &d);
    }
    free(page_table);
    free(frame_table);

}

void page_table_sizes( int **page_table, int *pages, int **frame_table, int *frames, int *page_size )
{
    int count, tmp, i;
    do
    {
        printf("How many frames are to be implemented: ");
        scanf("%d", frames);
        printf("How many pages are to be implemented (<= frames): ");
        scanf("%d", pages);
        if( frames < pages )
            printf( "frames must be greater than or equal to pages.");
    }while(frames < pages);
    
    do
    {
        count = 0;
        printf("Enter a block size for pages/frames (power of two ex 2, 4, 8, 16, 32...): ");
        scanf("%d", page_size);
        for( i = 0; i < 20; i++)
        {
            if( ( *page_size & ( 1 << i )) != 0 )
                count++;
        }
        if( count > 1)
            printf( "Size entered was not a power of two.\n" );
    }while( count != 1 );
    
    *frame_table = (int*)malloc( sizeof(int) * (*frames));
    *page_table = (int*)malloc( sizeof(int) *  (*pages) );
    
    for( i = 0; i < *frames; i++ )
        *frame_table[i] = -1;
    tmp = rand() % *frames;
    
    for( i = 0; i < *pages; i++ )
    {
        while( *frame_table[tmp] != -1 ) 
            tmp = rand() % *frames;
        *page_table[i] = tmp;
        *frame_table[tmp] = i;
    }
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
            printf("Entry found in page %d.\n Accessing frame %d with offset of %d bytes", i, page_table[i], *d);
            access_physical_mem( d, &page_table[i], frames, page_size);
        }
    }
    if(!found)
        printf("Entry not found in page table. Tried accessing %d.", *p);
}

void access_physical_mem( const int *d, const int *frame, const int *frames, const int *page_size)
{
    int tmp, total_mem;
    //sleep for 1 second to simulate access time to physical memory
    sleep(1);
    if( *d < *page_size)
        printf("Frame, %d, with offset, %d, accessed successfully.\n", *frame, *d);
    else
    {
        tmp = (*frame) * (*page_size) + *d;
        total_mem = (*frames) * (*page_size);
        if( tmp >= total_mem )
            printf("The offset, %d, accessed non existent memory.\n", *d);
        else
            printf("The offset, %d, accessed frame, %d, not in page table.\n", *d, tmp%total_mem);
    }
}
