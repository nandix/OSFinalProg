/* A sample program to demonstrate shared memory.  It uses
the following functions:  shmget, shmat, shmctl.  The man pages
will describe the functions.   */


#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>     
#include <sys/shm.h>
#include <errno.h>
#include <unistd.h>

#define SHMKEY 1066
#define K 1024
                                                  
int main () {

  int shmid; 
  int i;
  int pid;
  int opid;
  int *pint;
  char *addr;

  printf ("A shared memory test\n");

  // Using SHMKEY, create one shared memory region with access permissions 0666:
  shmid = shmget(SHMKEY, 10*K, IPC_CREAT | IPC_EXCL | 0666);
  printf ("Shared memory id = %d\n", shmid);
  if ( shmid < 0)
  {
    printf("***ERROR: shmid is %d\n", shmid);
    perror("shmget failed");
    exit(1);
  }  

  //attach the shared memory to process:
  addr =  shmat(shmid, 0, 0);
  printf("addr 0x%x\n", addr);

  // Setup a pointer to address an array of integers:
  pint = (int *) addr;


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

  shmctl(shmid, IPC_RMID, 0);

  return 0;

}

