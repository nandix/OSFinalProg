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
    int p, d;
    page_table_sizes( &page_table, &pages, &frame_table, &frames, &page_size );
    
    printf("How many iterations to run: ");
    scanf("%d", &iterations );

    for( i = 0; i < iterations; i++ )
    {
        p = rand() % pages;
        d = rand() % (page_size * 2);
        paging_algorithm( page_table, &pages, frame_table,  &frames, &page_size, &p, &d);
    }

}

void page_table_sizes( int **page_table, int *pages, int **frame_table, int *frames, int *page_size )
{
    int count;
    int i;
    do
    {
        printf("How many frames are to be implemented: ");
        scaanf("%d", &frames);
        printf("How many pages are to be implemented (<= frames): ");
        scanf("%d", &pages);
        if( frames < pages )
            printf( "frames must be greater than or equal to pages.");
    }while(frames < pages);
    
    do
    {
        count = 0;
        printf("Enter a block size for pages/frames (power of two ex 2, 4, 8, 16, 32...): ");
        scanf("%d", &page_size);
        for( i = 0; i < 20; i++)
        {
            if( ( page_size & ( 1 << i )) != 0 )
                count++;
        }
        if( count > 1)
            printf( "Size entered was not a power of two.\n" );
    }while( count != 1 );
    
    *frame_table = (int*)malloc( sizeof(int) * (*frames));
    *page_table = (int*)malloc( sizeof(int) *  (*pages) );
    
    for( i = 0; i < *frames; i++ )
        frame_table[i] = -1;
    tmp = rand() % *frames;
    
    for( i = 0; i < *pages; i++ )
    {
        while( frame[tmp] != -1 ) 
            tmp = rand() % *frames;
        page_table[i] = tmp;
        frame_table[tmp] = i;
    }
}

void paging_algorithm( int *page_table, int * pages, int *frame_table, int *frames, int *page_size, int *p, int *d )
{
    int i;
    bool found = false;
    printf( "Looking for %d in page table:\n");
    for( i = 0; i < *pages && !found; i++)
    {
        if( i == *p )
        {
            printf("Entry found in page %d and frame %d with offset of %d bytes", i, page_table[i], *d);
            if( *d < *page_size)
                found = true;
            else
            {
                
            }
        }

    }
    if(!found)
    {
        printf("Entry not found in page table. Tried accessing %d.")
    }
}


