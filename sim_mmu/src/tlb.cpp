#include "../include/tlb.h"
void tlb(void)
{
    typedef void (*fp)( int *, int *, int *, int *);
    int i;
    int input;
    int pages;
    int page_size;
    int iterations;
    int num_tlb;
    int *tlb_pages;
    int *frames;    
    int *page_table;
    int frame_num;
    int page;
    fp tlb_replacements[3];
    tlb_replacements[0] = tlb_miss_random;
    tlb_replacements[1] = tlb_miss_round_robin;
    tlb_replacements[2] = tlb_miss_least_used;

    page_table_sizes( &pages, &page_size, &page_table);
    input = tlb_replacement();
    tlb_set_up( &tlb_pages, &num_tlb, &iterations, &frames, pages);

    for( i = 0; i < iterations; i ++)
    {
        if( !in_tlb( tlb_pages, frames, &num_tlb, &page, &frame_num  ) )
        {
            tlb_replacements[input]( tlb_pages, page_table, &num_tlb, &pages );
            paging_algorithm( &pages, &page_size, page_table, &page, &frame_num);
        }
    }
}




void tlb_set_up( int **tlb_pages, int *num_tlb, int *iterations, int **frames, int *pages)
{
    int i, tmp;
    printf("How many entries in TLB? ( 0 for random number between 32 and 1024 ): ");
    scanf( "%d", &num_tlb );

    if( num_tlb <= 0 )
    {
        *num_tlb = rand() % 1025;
        *num_tlb += (*num_tlb < 32) ? 32 : 0;
    }
    *tlb_pages = (int*)malloc( sizeof( int ) * (*num_tlb) );
    *frames = (int*)malloc( sizeof(int) * (*num_tlb));
    printf("How many iterations to run? ");
    scanf( "%d", &iterations );

    for( i = 0; i < num_tlb; i++ )
        *tlb_pages[i] = -1;
    
    tmp = rand() % *pages;
    for( i = 0; i < num_tlb; i++ )
    {
        while( tlb_pages[tmp] == -1)
            tmp = rand() % *pages;
        tlb_pages[i] = tmp;
    }
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
    return input;
}

bool in_tlb( const int *tlb_pages, const int *frames, const int *num_tlb, const int *page, int *frame_num )
{
    int i;
    bool exists = false;
    printf("Searching TLB for: %d\n", page );
    printf("\tPage Number\tFrame Number\n");
    for( i = 0; i < *num_tlb; i++ )
    {
        printf("\t%d\t%d\n",tlb_pages[i], frames[i]);
    }

    for( i = 0; i < *num_tlb; i++ )
    {
        if( tlb_pages[i] == *page )
        {
            printf("Page Found in TLB.\n");
            *frame_num = frames[i]; 
            exists = true;
        }
    }
    if(!exists)
        printf("Page Not Found in TLB.\n");
    return exists;
}

void tlb_miss_random(int *tlb_pages, int* pages, int* max_tlb, int* max_pages)
{
       
}

void tlb_miss_round_robin( int *tlb_pages, int* pages, int* max_tlb, int* max_pages)
{

}

void tlb_miss_least_used( int *tlb_pages, int* pages, int* max_tlb, int *max_pages)
{

}
