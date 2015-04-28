#include "../include/tlb.h"
#include "../include/reloc.h"
#include "../include/paging.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
int main( int argc, char **argv )
{   
    typedef void (*fp)(void);
    fp mmu_options[3];
    mmu_options[0] = relocation_register;
    mmu_options[1] = paging;
    mmu_options[2] = tlb;

    int input = 1;
    do
    {
        printf("Memory Management Unit (MMU) Simulation Options:\n");
        printf("1) MMU with relocation register\n");
        printf("2) MMU with Paging\n");
        printf("3) MMU with translation look-aside buffer (TLB)\n");
        printf("4) exit the program\n");
        printf("User selection: ");
        scanf("%d", &input );
        if( input > 4 || input < 1)
            printf( "\n\nInvalid choice. Valid choices are: 1, 2, 3, 4\n\n");
        else if( input!= 4 )
            mmu_options[input-1]();
    }while( input != 4 );
}
