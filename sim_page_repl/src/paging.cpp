#include "../include/paging.h"


/**
 *  Function: create_frame_table
 *
 *  Author: Dan Nix
 *  
 *  Description: Creates a table to simulate frames in physical
 *                  memory given a user supplied size.
**/
void create_frame_table( page **frame_table, int *frames )
{
    int i;
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

/**
 *  Function: create_page_list
 *
 *  Author: Dan Nix
 *  
 *  Description: Generates a random list of pages in a user supplied 
 *                  range and length.
**/
void create_page_list( int *frames, page **page_list, int *pages, int *page_requests ){

    int i;
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

/**
 *  Function: page_miss
 *
 *  Author: Dan Nix
 *  
 *  Description: Indicates if the table already has a requested page, if 
 *                  there is an empty frame to put a new page, or if there
 *                  was a page miss.
**/
int page_miss( page *p, page ** frame_table, int size ){

    int i;
    for( i=0; i<size; i++ ){
        if( (*frame_table)[i].page_num == (*p).page_num ){
            (*frame_table)[i].lru_time = clock();
            return PAGE_IN_TABLE;
        }
        else if( (*frame_table)[i].page_num == -1 ){
            return EMPTY_FRAME;
        }
    }

    return PAGE_MISS;
}

/**
 *  Function: insert_in_open
 *
 *  Author: Dan Nix
 *  
 *  Description: If page_miss indicated there was an empty page
 *                   this function inserts it into the first empty
 *                   frame
**/

int insert_in_open( page *p, page ** frame_table, int size ){
    int i;

    for( i=0; i<size; i++ ){

        if( (*frame_table)[i].page_num == (*p).page_num ){
            printf( "Already in page table\n");
            return i;
        }
        if( (*frame_table)[i].page_num == -1 ){

            (*p).frame_num = i;
            (*frame_table)[i] = *p;
            return i;
        }
    }

    return -1;

}

/**
 *  Function: print_frame_table
 *
 *  Author: Dan Nix
 *  
 *  Description: Helper function to print a frame table in an easy-to-read
 *                   format
**/
void print_frame_table(page **frame_table, int frames, bool print_time ){
    int i;
    for( i = 0; i < frames; i++ ){
        if( print_time == false){
            printf("Frame %d: P(%d) F(%d)\n", 
                i, (*frame_table)[i].page_num, (*frame_table)[i].frame_num );
        }
        else{
            printf("Frame %d: P(%d) F(%d) T(%ld)\n", 
                i, (*frame_table)[i].page_num, (*frame_table)[i].frame_num, (*frame_table)[i].lru_time );
        }
    }
}


/**
 *  Function: find_optimal_repl
 *
 *  Author: Dan Nix
 *  
 *  Description: finds the index of the page to be selected as the victem
 *                   using the optimal replacement algorithm. It returns 
 *                   the index of the victim frame.
**/
int find_optimal_repl(page **frame_table, page **page_list, int frames, int page_requests, int pos ){

    int index = -1;
    int longest = 0;
    int count;

    int i,j;

    if( pos == page_requests - 1 ){
        return 0;
    }

    for( i=0; i<frames; i++ ){
        count = 0;
        for( j=pos; j<page_requests; j++ ){
            // compare each frame in table to next occurnece in list
            if( (*page_list)[j].page_num != (*frame_table)[i].page_num ){
                count++;
            }
            else{
                break;
            }
        }
        if( count > longest ){
            longest = count;
            index = i;
            continue;
        }
    }

    return index;
}

/**
 *  Function: find_lru_repl
 *
 *  Author: Dan Nix
 *  
 *  Description: finds the index of the page to be selected as the victem
 *                   using the LRU replacement algorithm. It returns 
 *                   the index of the victim frame.
**/
int find_lru_repl( page **frame_table, int frames ){
    
    int i;
    int index = -1;
    long cur_lru_time = (*frame_table)[0].lru_time + 1;

    for( i=0; i < frames; i++ ){
        if( (*frame_table)[i].lru_time < cur_lru_time ){
            index = i;
            cur_lru_time = (*frame_table)[i].lru_time;
        }
    }

    return index;
}

/**
 *  Function: find_lfu_repl
 *
 *  Author: Dan Nix
 *  
 *  Description: finds the index of the page to be selected as the victem
 *                   using the LFU replacement algorithm. It returns 
 *                   the index of the victim frame.
**/
int find_lfu_repl( page **frame_table, int frames, vector<int> page_counts ){
    int i;
    int index = -1;
    int lfu_min = 1000000000;

    for( i=0; i < frames; i++ ){
        if( page_counts[(*frame_table)[i].page_num] < lfu_min ){
            index = i;
            lfu_min = page_counts[(*frame_table)[i].page_num];
        }
    }

    return index;
}

/**
 *  Function: find_second_chance_repl
 *
 *  Author: Dan Nix
 *  
 *  Description: finds the index of the page to be selected as the victem
 *                   using the second_chance replacement algorithm. It returns 
 *                   the index of the victim frame.
**/
int find_second_chance_repl( page **frame_table, int frames ){
    
    int i;
    int index = -1;
    long cur_lru_time = (*frame_table)[0].lru_time + 1;

    while( index == -1 ){
        for( i=0; i < frames; i++ ){
            if( (*frame_table)[i].second_chance == 1){
                (*frame_table)[i].second_chance--;
            }
            else if( (*frame_table)[i].lru_time < cur_lru_time ){
                index = i;
                cur_lru_time = (*frame_table)[i].lru_time;
            }
        }
    }

    return index;
}