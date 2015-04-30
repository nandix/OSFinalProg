
#include "../include/paging.h"
#include "../include/paging_algorithms.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
int main( int argc, char **argv )
{   
    typedef void (*fp)(void);
    fp repl_options[3];
    repl_options[0] = fifo_alg;
    repl_options[1] = optimal_alg;
    repl_options[2] = lru_alg;

    int input = 1;



    srand ( time(NULL) );
    do
    {
        printf("\nPage Replacement Simulation Options:\n");
        printf("1) FIFO Algorithm\n");
        printf("2) Optimal Algorithm\n");
        printf("3) LRU Algorithm\n");
        printf("4) exit the program\n");
        printf("User selection: ");
        scanf("%d", &input );
        if( input > 4 || input < 1)
            printf( "\n\nInvalid choice. Valid choices are: 1, 2, 3, 4\n\n");
        else if( input!= 4 )
            repl_options[input-1]();
    }while( input != 4 );
}
