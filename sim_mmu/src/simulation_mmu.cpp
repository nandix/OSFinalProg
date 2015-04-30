 /************************************************************************
   Program: MMU Simulator
   Author: Christopher Smith, Dan Nix, Matt Rames
   Class: Operating Systems
   Instructor:Dr. Karlsson
   Date: 30 April 2015
   
   Description:    This program simulates the memory management unit and
   the different methods for accessing physical memory with logical memory.
   It implements the simple relocation register that is just an offset. and the
   paging scheme without a TLB as well as a version with the TLB. The TLB simulates
   if there is a miss the replacement schemes of random, round robin, and least recently used.
   
   Input: Prompt driven
   Output:What the physical memory getting, accessed the pages and associated frames, tlb table after every replacement
   
   Compilation instructions: make
   Usage: mmu_simulation or ./mmu_simulation
   
   Known bugs/missing features:No known bugs
 ************************************************************************/



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

    srand ( time(NULL) );
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
