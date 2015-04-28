#include "../include/tlb.h"
#include "../include/paging.h"
void tlb(void)
{
    typedef void (*fp)( int *, int *, int *, int *, int *);
    int i, input, iterations, p, d;
    //TLB specific variables
    int num_tlb;
    int *tlb_pages, *tlb_frames;
    //page and frame array
    int *page_table, *frame_table;
    //number of pages and frames and size in bytes
    int pages, frames, page_size;

    fp tlb_replacements[3] = { tlb_miss_random, tlb_miss_round_robin, tlb_miss_least_used};

    page_table_sizes( &page_table, &pages, &frame_table, &frames, &page_size);
    tlb_set_up( &tlb_pages, &tlb_frames, &num_tlb, page_table, &pages);
    input = tlb_replacement();
    
    printf("How many iterations to run: ");
    scanf( "%d", &iterations );
    
    for( i = 0; i < iterations; i ++)
    {   
        p = rand() % page_size;
        d = rand() % (frames * 2);
        if( !in_tlb( tlb_pages, tlb_frames, &num_tlb, &page_size, &frames,  &p, &d  ) )
        {
            tlb_replacements[input]( tlb_pages, tlb_frames, page_table, &num_tlb, &pages);
            paging_algorithm( page_table, &pages, frame_table, &frames, &page_size, &p, &d);
        }
    }    
    free( tlb_pages );
    free( tlb_frames );
    free( page_table );
    free( frame_table );
}

void tlb_set_up( int **tlb_pages,int **tlb_frames,  int *num_tlb, int *page_table, int *pages)
{
    int i, tmp;
    printf("How many entries in TLB? (  0 for random number between 32 and 1024 ): ");
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
        *tlb_pages[i] = -1;
    
    tmp = rand() % *pages;
    for( i = 0; i < *num_tlb; i++ )
    {
        while( *tlb_pages[tmp] == -1)
            tmp = rand() % *pages;
        *tlb_pages[i] = tmp;
        *tlb_frames[i] = page_table[tmp];
    }
    printf("The TLB table:\n");
    for( i = 0; i < *num_tlb; i++ )
        printf("Entry %d contains page %d and frame refrence %d\n",i, (*tlb_pages)[i], (*tlb_frames)[i]);
}

int tlb_replacement( )
{
    int input;
    do
    {
        printf("\n\nTLB replacement policies to choose from: \n" );
        printf("1) Random\n2) Round Robin\n3) Least Recently Used\n");
        printf("User Choice (1,2, or 3): ");
        scanf( "%d", &input );
    }while( input < 1 && input > 3 );
    return input - 1;
}

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

void tlb_miss_random(int *tlb_pages, int* tlb_frames, int* pages, int* max_tlb, int* max_pages)
{
       
}

void tlb_miss_round_robin( int *tlb_pages, int* tlb_frames, int* pages, int* max_tlb, int* max_pages)
{

}

void tlb_miss_least_used( int *tlb_pages, int* tlb_frames, int* pages, int* max_tlb, int *max_pages)
{

}
