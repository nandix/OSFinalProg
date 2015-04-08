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



using namespace std;

// Usage strings
const string CMDNM_USAGE = "cmdnm <pid>";
const string PID_USAGE = "pid <command>";
const string SYSTAT_USAGE = "systat";
const char* DASHES = (const char*)"-----------------------------------------------------------\n";

const bool DEBUGGING = false;