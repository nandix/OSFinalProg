/* 
This is a modified version of Karlsson's original example code 
to learn to allocate multiple blocks of memory and read from them.

A sample program to demonstrate shared memory.  It uses
the following functions:  shmget, shmat, shmctl.  The man pages
will describe the functions.   */


#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>     
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>

#define SHM_BASE_KEY 2015
#define K 1024
                                                  
int main () {

  int* shmid; 
  int i;
  int pid;
  int opid;
  char **addr;
  int *pint;

  int num_blocks;
  int block_size;
  int block_to_use;

  printf ("A shared memory test\n");

  printf("How many blocks would you like to allocate: " );
  scanf("%d", &num_blocks);

  printf("What size (in bytes) should each block be: ");
  scanf("%d", &block_size);

  // Allocate enough space to hold the shared memory ids.
  shmid = (int*) malloc(num_blocks*sizeof(int));
  addr = (char**) malloc(num_blocks*sizeof(char*));


  // Using SHMKEY, create one shared memory region with access permissions 0666:
  for( i = 0; i < num_blocks; i++ ){
    shmid[i] = shmget(SHM_BASE_KEY + i, block_size, IPC_CREAT | IPC_EXCL | 0666);

    printf ("Shared memory id = %d\n", shmid[i]);
    if ( shmid[i] < 0)
    {
      printf("***ERROR: shmid is %d\n", shmid[i]);
      perror("shmget failed");
      exit(1);
    } 

    //attach the shared memory to process:
    addr[i] =  shmat(shmid[i], 0, 0);
    printf("addr 0x%x\n", addr[i]);
  }


  printf("What block would you like to use: " );
  scanf("%d", &block_to_use);

  while(block_to_use >= num_blocks){
    printf("Highest block index is %d. Try again: ", num_blocks );
    scanf("%d", &block_to_use);
  }

  // Setup a pointer to address an array of integers:
  pint = (int *) addr[block_to_use];


  printf("Prior to fork\n");
  pid = fork();

  if (pid == 0) {
    printf("In child, after fork\n");
    printf("Sleep for 2 seconds while parent writes data\n");

    sleep(2);
    // Read data back and write to stdout:
    for (i=0;i<128;i++)  
      printf("index = %d\t value = %d\n", i, *(pint + i));
  
  } else {
    printf("In parent, after fork\n");

    // Write data into shared memory block:
    for (i=0;i<128;i++)  {
      *(pint + i) = 128 - i;
      printf(".");
    }
    printf("\n");
    wait(NULL);

  }
    printf("\n");
  for( i = 0; i < num_blocks; i++ ){
    shmctl(shmid[i], IPC_RMID, 0);
  }

  return 0;

}

