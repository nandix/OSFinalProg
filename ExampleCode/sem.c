/* A sample program to demonstrate semaphores.  It uses
the following functions:  semget, semop, semctl.  The man pages
will describe the functions.  */


#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>     
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>

#define SEMKEY 1066

// This is defined in linux/sem.h
// Included here....
union semun 
{
  int              val;       /* value for SETVAL */
  struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
  unsigned short int *array;  /* array for GETALL, SETALL */
  struct seminfo *__buf;      /* buffer for IPC_INFO */
};
                                                  
int main () {

  int id; 
  int i;
  int opid;
  
  struct sembuf lock;  
  union semun options;
  
  printf ("A semaphore test\n");

  // Using SEMKEY, create one semaphore with access permissions 0666:
  id = semget(SEMKEY, 1, IPC_CREAT | IPC_EXCL | 0666);
  printf ("Semaphore id = %d\n", id);
  
  // Initialize the semaphore at index 0
  options.val = 1;
  semctl(id , 0, SETVAL, options); 
  
  // Test that the semaphore was created correctly:
  if (semctl(id, 0, GETVAL, 0) ==0 ) {
    printf ("can not lock semaphore.\n");
    exit(1);
  }
  
  // print the value of the semaphore:
  i = semctl(id, 0, GETVAL, 0);
  printf ("Value of semaphore at index 0 is %d\n", i);
  
  // Set the semaphore:
  lock.sem_num = 0;  // semaphore index
  lock.sem_op = -1; // the operation
  lock.sem_flg = IPC_NOWAIT;  // operation flags
  opid = semop(id, &lock, 1);  // perform the requested operation
  
  // signal if an error occured
  if (opid == -1 ) {
    printf ("can not lock semaphore.\n");
    exit(1);
  }
  
  // print the value of the semaphore
  i = semctl(id, 0, GETVAL, 0);
  printf ("Value of semaphore at index 0 is %d\n", i);
  
  // Unset the semaphore:
  lock.sem_num = 0; // semaphore index
  lock.sem_op = 1; // the operation
  lock.sem_flg = IPC_NOWAIT; // operation flags
  opid = semop(id, &lock, 1); // perform the requested operation
  
  // signal if an error occured
  if (opid == -1 ) {
    printf ("can not unlock semaphore.\n");
    exit(1);
  }
  
  // print the value of the semaphore
  i = semctl(id, 0, GETVAL, 0);
  printf ("Value of semaphore at index 0 is %d\n", i);
  
  // remove the semaphore
  semctl(id, 0, IPC_RMID, 0);
  return (0);
}

