 /************************************************************************
   Program: MMU Simulator
   File: tlb.cpp
   Author: Christopher Smith, Dan Nix, Matt Rames
   Class: Operating Systems
   Instructor:Dr. Karlsson
   Date: 30 April 2015
   
   Description:    This file contains all the code for the basic paging algorithm
   Input: Prompt driven
   Output: The page and associated frames, The offset that will access
   within a frame and if it stays within the current frame or is in another frame.
   Also TLB table will be printed and as a entry is replaced it will be reprinted.
 ************************************************************************/



#include "../include/tlb.h"
#include "../include/paging.h"

/************************************************************************
*   Function: void tlb(void)
*   Description: This is the start of the tlb algorithm and will call
*   the function for user input to give page and frame information. Also
*   it will ask the user how many entries to be in tlb and what replacement
*   scheme to use. It then will ask how many iterations (simulations) to run.
************************************************************************/
void tlb(void)
{
    typedef void (*fp)( int *, int *, int *, int *, int *, int *);
    int i, input, iterations, p, d;
    //TLB specific variables
    int tmp;
    int num_tlb;
    int *tlb_pages, *tlb_frames;
    //page and frame array
    int *page_table, *frame_table;
    //number of pages and frames and size in bytes
    int pages, frames, page_size;
    int *count;
    fp tlb_replacements[3] = { tlb_miss_random, tlb_miss_round_robin, tlb_miss_least_used};

    page_table_sizes( &page_table, &pages, &frame_table, &frames, &page_size);
    tlb_set_up( &tlb_pages, &tlb_frames, &num_tlb, page_table, &pages);
    input = tlb_replacement();
    if( input == 2 )
    {
        count = (int* ) malloc( sizeof( int ) * num_tlb);
        for( i = 0; i < num_tlb; i++)
            count[i] = 0;
    }
    else
    {
        count = (int* ) malloc( sizeof( int ) * pages );
        for( i = 0; i < pages; i++)
            count[i] = i;
        for( i = 0; i < num_tlb; i++ )
        {
            tmp = count[ pages - ( i + 1 ) ];
            count[ pages - ( i + 1 ) ] = tlb_pages[ i ];
            count[ tlb_pages[ i ]  ] = tmp;
        }
            
    }
    printf("How many iterations to run: ");
    scanf( "%d", &iterations );
    printf("\n\n");
    
    for( i = 0; i < iterations; i ++)
    {   
        p = rand() % pages;
        d = rand() % (page_size * 2);
        if( !in_tlb( tlb_pages, tlb_frames, &num_tlb, &page_size, &frames,  &p, &d  ) )
        {
            tmp = p;
            if( input == 1 )
                p = pages;
            tlb_replacements[input]( tlb_pages, tlb_frames, page_table, &num_tlb, count, &p);
            p = tmp;
            paging_algorithm( page_table, &pages, frame_table, &frames, &page_size, &p, &d);
        }
    }    
    free( tlb_pages );
    free( tlb_frames );
    free( page_table );
    free( frame_table );
}
/************************************************************************
*   Function: void tlb_set_up(int **tlb_pages, int **tlb_frames, 
*                             int *num_tlb, int *page_table, int *pages )
*   Description: This function will ask the user how many tlb entries they
*   would like and then prints the table created.
************************************************************************/
void tlb_set_up( int **tlb_pages,int **tlb_frames,  int *num_tlb, int *page_table, int *pages)
{
    int i, j, tmp;
    printf("How many entries in TLB (any number is fine, but 0 for random number between 32 and 1024): ");
    scanf( "%d", num_tlb );

    if( num_tlb <= 0 )
    {
        *num_tlb = rand() % 1025;
        *num_tlb += (*num_tlb < 32) ? 32 : 0;
        printf("%d entries will be created and randomly assigned pages.\n", *num_tlb);
    }
    *tlb_pages =  (int*)malloc( sizeof( int ) * (*num_tlb) );
    *tlb_frames = (int*)malloc( sizeof( int ) * (*num_tlb) );
    for( i = 0; i < *num_tlb; i++ )
        (*tlb_pages)[i] = -1;

    for( i = 0; i < *num_tlb; i++ )
    {
        tmp = rand() % *pages;
        for( j = 0; j < i; j++ )
        {
            if( (*tlb_pages)[j] == tmp )
            {
                j = -1;
                tmp = rand() % (*pages);
            }
        }
        (*tlb_pages)[i] = tmp;
        (*tlb_frames)[i] = page_table[tmp];
    }
    print_tlb( *tlb_pages, *tlb_frames, num_tlb);
}
/************************************************************************
*   Function: void tlb_replacement() 
*   Description: This function will ask the user which tlb replacement policy to use
************************************************************************/
int tlb_replacement( )
{
    int input;
    do
    {
        printf("TLB replacement policies to choose from: \n" );
        printf("1) Random\n2) Round Robin\n3) Least Recently Used\n");
        printf("User Choice (1,2, or 3): ");
        scanf( "%d", &input );
    }while( input < 1 && input > 3 );
    return input - 1;
}
/************************************************************************
*   Function: void in_tlb( const int *tlb_pages, const int *tlb_frames, 
*                          const int *num_tlb, const int *page_size, 
*                          const int *frames, const int *p, const int *d) 
*   Description: This function will search the tlb page table for a given
*   page and then display if it is not found in tlb or if it is. If it is
*   the program will go directly to physical memory access.
************************************************************************/
bool in_tlb( const int *tlb_pages, const int *tlb_frames, const int *num_tlb, const int *page_size, const int *frames, const int *p, const int *d)
{
    int i;
    bool exists = false;
    printf("Searching TLB for: %d\n", *p );

    for( i = 0; i < *num_tlb; i++ )
    {
        if( tlb_pages[i] == *p )
        {
            printf("Page Found in TLB.\n");
            access_physical_mem( d, &tlb_frames[i], frames, page_size);
            exists = true;
        }
    }
    if(!exists)
        printf("Page Not Found in TLB.\n");
    return exists;
}
/************************************************************************
*   Function: void tlb_miss_random( int *tlb_pages, int *tlb_frames, 
*                          int *page_table, int *max_tlb, 
*                          int *count, int *p) 
*   Description: This function will randomly select an entry in the tlb
*   and replace it with the page that was trying to be selected
************************************************************************/
void tlb_miss_random(int *tlb_pages, int* tlb_frames, int* page_table, int* max_tlb, int *count, int* p)
{
    int tmp = rand() % *max_tlb;
    tlb_pages[tmp] = *p;
    tlb_frames[tmp] = page_table[*p];
    for( int i = 0; i < *max_tlb; i++)
        if(count[i] > 0 )
            count[i]--;
    count[tmp] = 0;
    print_tlb( tlb_pages, tlb_frames, max_tlb);
}
/************************************************************************
*   Function: void tlb_miss_round_robin( int *tlb_pages, int *tlb_frames, 
*                          int *page_table, int *max_tlb, 
*                          int *count, int *p) 
*   Description: This function will select the next page in the que (count array)
*   that is to be entered into the tlb. The removed tlb page will then be sent to
*   the back of the que.
************************************************************************/
void tlb_miss_round_robin( int *tlb_pages, int* tlb_frames, int* page_table, int* max_tlb, int *count, int* p)
{
    int i, tmp;
    tmp = tlb_pages[0];
    for( i = 0; i < *max_tlb-1; i++)
    {
        tlb_pages[i] = tlb_pages[ i + 1];
        tlb_frames[i] = tlb_frames[i+1];
    }
    tlb_pages[*max_tlb-1] = count[0];
    tlb_frames[*max_tlb-1] = page_table[count[0]];
    for( i = 0; i < *p; i++ )
        count[i] = count[ i + 1];
    count[*p - 1] = tmp;
    print_tlb( tlb_pages, tlb_frames, max_tlb);
}
/************************************************************************
*   Function: void tlb_miss_least_used( int *tlb_pages, int *tlb_frames, 
*                          int *page_table, int *max_tlb, 
*                          int *count, int *p) 
*   Description: This function will select the tlb entry that hasn't been
*   used as often as the others. in case of 2 or more but not all not being used
*   the same the first found will be used. If all entries are used equally 
*   a random one is selected.
************************************************************************/
void tlb_miss_least_used( int *tlb_pages, int* tlb_frames, int* page_table, int* max_tlb, int* count, int *p)
{
    int i;
    int tmp = 0;
    int loc = -1;
    for( i = 0; i < *max_tlb; i++)
        if( count[tmp] < count[i])
            tmp = loc = i;
    if( loc == -1 )
        tlb_miss_random( tlb_pages, tlb_frames, page_table, max_tlb,count, p);
    else
    {
        tlb_pages[loc] = *p;
        tlb_frames[loc] = page_table[*p];
        for( i = 0; i < *max_tlb; i++)
            if( count[i] > 0 )
                count[i]--;
        count[loc] = 0;
    
        print_tlb( tlb_pages, tlb_frames, max_tlb);
    }
}
/************************************************************************
*   Function: void print_tlb( int *tlb_pages, int *tlb_frames, int *num_tlb 
*   Description: This function will print the entries in the tlb table
************************************************************************/
void print_tlb( int *tlb_pages, int * tlb_frames, int *num_tlb)
{
    int i;
    printf("The TLB table:\n");
    for( i = 0; i < *num_tlb; i++ )
        printf("Entry %d contains page %d and frame refrence %d\n",i, tlb_pages[i], tlb_frames[i]);
    printf("\n\n");
}
