/**
 * Program: dash
 *
 * Author: Dan Nix
 *
 * Description: 
 *      The second implementation of Dash expands functionality to include:
 *          - Implement any system command with child process statistics      
 *          -  Implement the ``cd" command       
 *          -  Redirect input and output
 *          -  Pipe from one process to another
 *          -  Send and receive signals to and from other processes
 *      Detailed description of how each function is achieved is provided in
 *      prog2.pdf.
 */

// dirent.h is used for directories
#include <dirent.h>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <vector>

// Includes from Karlsson's code
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 
#include <stdio.h> 

//Needed for getrusage
#include <sys/time.h>
#include <sys/resource.h>

//Needed for redirection
#include <fcntl.h>
#include <sstream>

#include <signal.h>

//Needed for mailbox sharing
#include <sys/ipc.h>     
#include <sys/shm.h>
#include <errno.h>
#include <sys/sem.h>



using namespace std;

const int KB = 1024; // number of bytes in a kilobyte
const int SHMKEY = 1066;
const int SEMKEY = 1066;


// Usage strings
const string CMDNM_USAGE = "cmdnm <pid>";
const string PID_USAGE = "pid <command>";
const string SYSTAT_USAGE = "systat";
const char* DASHES = (const char*)"-----------------------------------------------------------\n";

const bool DEBUGGING = false;


union semun 
{
  int              val;       /* value for SETVAL */
  struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
  unsigned short int *array;  /* array for GETALL, SETALL */
  struct seminfo *__buf;      /* buffer for IPC_INFO */
};