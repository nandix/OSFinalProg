 /************************************************************************
   Program: MMU Simulator
   File: paging.cpp
   Author: Christopher Smith, Dan Nix, Matt Rames
   Class: Operating Systems
   Instructor:Dr. Karlsson
   Date: 30 April 2015
   
   Description:    This file contains all the code for the basic paging algorithm
   Input: Prompt driven
   Output: The page and associated frames, The offset that will access 
   within a frame and if it stays within the current frame or is in another frame.
 ************************************************************************/


#include "../include/paging.h"
/************************************************************************
*   Function: void paging(void)
*   Description: This is the start of the paging algorith and will call
*   the function for user input to give page and frame information. It
*   then will ask how many iterations (simulations) to run.
************************************************************************/
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
    printf("\n");
    for( i = 0; i < iterations; i++ )
    {
        p = rand() % pages;
        d = rand() % (page_size * 2);
        paging_algorithm( page_table, &pages, frame_table,  &frames, &page_size, &p, &d);
    }
    free(page_table);
    free(frame_table);
}
/************************************************************************
*   Function: page_table_sizes( int **page_table, int *pages, int **frame_table,
*                               int *frames, int *page_size )
*   Description: This function gets the user input for frames and pages 
*   and the block size of the two. Also will display the page table and 
*   what frames they reference.
************************************************************************/
void page_table_sizes( int **page_table, int *pages, int **frame_table, int *frames, int *page_size )
{
    int count, tmp, i;
    do
    {
        printf("How many frames are to be implemented: ");
        scanf("%d", frames);
        printf("How many pages are to be implemented (<= frames): ");
        scanf("%d", pages);
        if( *frames < *pages )
            printf( "frames must be greater than or equal to pages.\n");
    }while(*frames < *pages);
    
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
/************************************************************************
*   Function: void paging(void)
*   Description: This function will find the page in the page table and
*   display that it is accessing a frame with a certain offset and call
*   the access_physical_mem function.
************************************************************************/
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
/************************************************************************
*   Function: void paging(void)
*   Description: This function will find the page in the frame table and
*   attempt to access the frame with the offset displays if successful
************************************************************************/

void access_physical_mem( const int *d, const int *frame, const int *frames, const int *page_size)
{
    int i;
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
        {
            tmp = *frame;
            for( i = 0; i < *d % *page_size; i++ )
                tmp++;
            printf("The offset, %d, accessed frame, %d, which is not associated with original look up.\n\n", *d, tmp  );
        }
    }
}
