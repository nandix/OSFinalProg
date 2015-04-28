#include "../include/reloc.h"
void relocation_register(void)
{
    int i;
    unsigned int base = 0;
    unsigned int max = rand() % 20000;
    unsigned int relocation = rand() % 20000;
    int iterations = 100;

    printf("\n\nHow many relocations are to be run? ");
    scanf( "%d", &iterations );
    printf("\nMin logical address space is: %u\n", base );
    printf("Max logical address space is: %u\n", max );
    printf("Relocation register is: %u\n", relocation);
    printf("Min physical address space is: %u\n", relocation);
    printf("Max physical address space is: %u\n\n", max + relocation);
    sleep(2);
    for( i = 0; i < iterations; i++ )
    {
        unsigned int address = rand()%20000;
        printf("Dynamic relocation using relocation register iteration: %d\n", i+1);

        printf("Logical address: %u\n", address);
        printf("Physical address: %u\n",address + relocation);
        if( address > max)
            printf("Segmentation fault\n\n");
        else
            printf("Memory accessed successfully\n\n");
    }
}
