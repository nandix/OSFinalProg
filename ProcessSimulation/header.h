 /************************************************************************
   Program: Process Scheduling Simulator
   File: header.h
   Author: Christopher Smith, Dan Nix, Matt Rames
   Class: Operating Systems
   Instructor:Dr. Karlsson
   Date: 30 April 2015
   
   Description: This file contains the libraries needed for the simulation and 
		the function prototypes.
   Output: The page and associated frames, The offset that will access 
   within a frame and if it stays within the current frame or is in another frame.
 ************************************************************************/
#include <iostream> // Used for standard input and output
#include <queue> // Used for queue's
#include <limits.h> // Used for MAX_INT



// Function Prototypes
void MainMenu();
void RoundRobin();
void FirstComeFirstServe();
void ShortestJobFirst();
void setProcessesRR(int num);
void setProcessesFCFS(int num);
void setProcessesSJF(int num);
void FCFSSimulation(int table[][3], int totalBurst, int num);
void SJFSimulation(int table[][3], int totalBurst, int num);
void RRSimulation(int table[][3], int totalBurst, int num, int quantum);

using namespace std;
