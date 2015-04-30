
#include "../include/paging.h"
#include "../include/paging_algorithms.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
int main( int argc, char **argv )
{   

    int input = 1;



    srand ( time(NULL) );
    do
    {
        printf("Page Replacement Simulation Options:\n");
        printf("1) FIFO Algorithm\n");
        printf("2) Optimal Algorithm\n");
        printf("3) LRU Algorithm\n");
        printf("4) exit the program\n");
        printf("User selection: ");
        scanf("%d", &input );
        if( input > 4 || input < 1)
            printf( "\n\nInvalid choice. Valid choices are: 1, 2, 3, 4\n\n");
        else if( input!= 4 )
            fifo_alg();
    }while( input != 4 );
}
