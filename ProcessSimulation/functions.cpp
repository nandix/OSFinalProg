 /************************************************************************
   Program: Process Scheduling Simulator
   File: functions.cpp
   Author: Christopher Smith, Dan Nix, Matt Rames
   Class: Operating Systems
   Instructor:Dr. Karlsson
   Date: 30 April 2015
   
   Description: This file contains all of the functions needed to run the
				various simulations.
 ************************************************************************/
#include "header.h"

/************************************************************************
*   Function: void MainMenu()
*   Description: This function prompts the user to make a selection
*   between the 3 different simulations or exit the application. Once
*  	the user makes a selection the function well call the assoicated 
*   function. 
************************************************************************/
void MainMenu()
{
	// Print menu prompt
	int selection = 0;
	cout << "1. Round Robin\n";
	cout << "2. Shortest Job First\n";
	cout << "3. First Come First Serve\n";
	cout << "4. Exit\n";
	cout << "Please Select a simulation: ";
	cin >> selection;

	switch (selection)
	{
		case 1:
			RoundRobin();
			break;
		case 2:
			ShortestJobFirst();
			break;
		case 3:
			FirstComeFirstServe();
			break;
		case 4:
			cout << "Exiting...\n";
			return;
			break;
		default:
			cout << "Invalid input, please enter a number above.\n";
			break;
	}
}

/************************************************************************
*   Function: void RoundRobin()
*   Description: This is the starting point of the Round Robin simulation
*	this function prompts the user for how many processes they want and
* 	passes the result to the next stage of the simulation.
************************************************************************/
void RoundRobin()
{
	int procNumber = 0;
	cout << "You selected: Round Robin" << endl;
	// Prompt for the number of processes
	cout << "Please enter how many processes you want (less than 10): ";
	cin >> procNumber;
	if(procNumber < 10 && procNumber > 0)
	{
		setProcessesRR(procNumber);
	}
	else
	{
		cout << "Invalid input, please enter number between 1 and 10.\n";
	}
}

/************************************************************************
*   Function: void FirstComeFirstServe()
*   Description: This is the starting point of the FCFS simulation
*	this function prompts the user for how many processes they want and
* 	passes the result to the next stage of the simulation.
************************************************************************/
void FirstComeFirstServe()
{
	int procNumber = 0;
	cout << "You selected: FirstComeFirstServe" << endl;
	// Prompt for the number of processes
	cout << "Please enter how many processes you want (less than 10): ";
	cin >> procNumber;
	if(procNumber < 10 && procNumber > 0)
	{
		setProcessesFCFS(procNumber);
	}
	else
	{
		cout << "Invalid input, please enter number between 1 and 10.\n";
	}
}

/************************************************************************
*   Function: void ShortestJobFirst()
*   Description: This is the starting point of the SJF simulation
*	this function prompts the user for how many processes they want and
* 	passes the result to the next stage of the simulation.
************************************************************************/
void ShortestJobFirst()
{
	int procNumber = 0;
	cout << "You selected: Shortet Job First" << endl;
	// Prompt for the number of processes
	cout << "Please enter how many processes you want (less than 10): ";
	cin >> procNumber;
	if(procNumber < 10 && procNumber > 0)
	{
		setProcessesSJF(procNumber);
	}
	else
	{
		cout << "Invalid input, please enter number between 1 and 10.\n";
	}

}

/************************************************************************
*   Function: void setProcessesRR(int num)
*   Description: This function prompts the user to enter a quantum as
*	well as the arrival time and burst time for each process. After
* 	the user has entered the information the process table is made. 
* 	All the information is then sent to the RR simulation function
* 	to preform the simulation.
************************************************************************/
void setProcessesRR(int num)
{
	int procArray[num][3];
	int arrival;
	int burst;
	int quantum;
	int totalBurst = 0;
	// Prompt for quantum and check output
	cout << "Please enter a quantum between 1 and 20: ";
	cin >> quantum;
	if (quantum < 1 || quantum > 20)
	{
		cout << "Invalid Quantum\n";
		return;
	}
	for(int i = 0; i < num; i++)
	{
		//Prompt for the arrival time and burst for each process
		cout << "Please input an arrival time for process " << i << ": ";
		cin >> arrival;
		// Make sure input is valid
		if (arrival < 0)
		{
			cout << "Invalid input\n";
			return;
		}
		cout << "Please input a burst time for process " << i << ": ";
		cin >> burst;
		// Make sure input is valid
		if (burst < 1)
		{
			cout << "Invalid input\n";
			return;
		}
		// Fill a 2D array that will store arrival and burst times
		procArray[i][0] = arrival;
		procArray[i][1] = burst;
	}


	// Loop through process table and output it to screen
	cout << "\nProcess table\n";
	cout << "Process		Arrival		Burst\n";
	for (int i = 0; i < num; i++)
	{
		cout << "p" << i << "		";
		cout << procArray[i][0] <<  "		";
		cout << procArray[i][1] << endl;
		totalBurst += procArray[i][1];
	}
	
	// Start the Round Robin simulation with collected data
	RRSimulation(procArray, totalBurst, num, quantum);
}

/************************************************************************
*   Function: void setProcessesFCFS(int num)
*   Description: This function prompts the user to enter the 
*	arrival time and burst time for each process. After
* 	the user has entered the information the process table is made. 
* 	All the information is then sent to the FCFS simulation function
* 	to preform the simulation.
************************************************************************/
void setProcessesFCFS(int num)
{
	int procArray[num][3];
	int arrival;
	int burst;
	int totalBurst = 0;
	for(int i = 0; i < num; i++)
	{
		//Prompt for the arrival time and burst for each process
		cout << "Please input an arrival time for process " << i << ": ";
		cin >> arrival;
		// Make sure input is valid
		if (arrival < 0)
		{
			cout << "Invalid input\n";
			return;
		}
		cout << "Please input a burst time for process " << i << ": ";
		cin >> burst;
		// Make sure input is valid
		if (burst < 1)
		{
			cout << "Invalid input\n";
			return;
		}
		// Fill a 2D array that will store arrival and burst times
		procArray[i][0] = arrival;
		procArray[i][1] = burst;
	}

	// Loop through process table and output it to screen
	cout << "\nProcess table\n";
	cout << "Process		Arrival		Burst\n";
	for (int i = 0; i < num; i++)
	{
		cout << "p" << i << "		";
		cout << procArray[i][0] <<  "		";
		cout << procArray[i][1] << endl;
		totalBurst += procArray[i][1];
	}
	
	// Start the First Come First Serve simulation with collected data
	FCFSSimulation(procArray, totalBurst, num);
}

/************************************************************************
*   Function: void setProcessesSJF(int num)
*   Description: This function prompts the user to enter the 
*	arrival time and burst time for each process. After
* 	the user has entered the information the process table is made. 
* 	All the information is then sent to the SJF simulation function
* 	to preform the simulation.
************************************************************************/
void setProcessesSJF(int num)
{
	int procArray[num][3];
	int arrival;
	int burst;
	int totalBurst = 0;
	for(int i = 0; i < num; i++)
	{
		//Prompt for the arrival time and burst for each process
		cout << "Please input an arrival time for process " << i << ": ";
		cin >> arrival;
		// Make sure input is valid
		if (arrival < 0)
		{
			cout << "Invalid input\n";
			return;
		}
		cout << "Please input a burst time for process " << i << ": ";
		cin >> burst;
		// Make sure input is valid
		if (burst < 1)
		{
			cout << "Invalid input\n";
			return;
		}
		// Fill a 2D array that will store arrival and burst times
		procArray[i][0] = arrival;
		procArray[i][1] = burst;
	}

	// Loop through process table and output it to screen
	cout << "\nProcess table\n";
	cout << "Process		Arrival		Burst\n";
	for (int i = 0; i < num; i++)
	{
		cout << "p" << i << "		";
		cout << procArray[i][0] <<  "		";
		cout << procArray[i][1] << endl;
		totalBurst += procArray[i][1];
	}
	// Start the Shortest Job First simulation with collected data
	SJFSimulation(procArray, totalBurst, num);
}

/************************************************************************
*   Function: void FCFSSimulation(int table[][3], int totalBurst, int num)
*   Description:This function outputs how the FCFS simulation works and 
* 	also outputs each step as processes are ran. It outputs when a process
* 	starts and finishes and will also output if the system is idle. 
************************************************************************/
void FCFSSimulation(int table[][3], int totalBurst, int num)
{
	queue<int> pqueue;
	int currentProcess;
	int length = 0;

	// Print output explaining FCFS
	cout << "\nBeginning simulation...\n";
	cout << "In First Come First Serve process scheduling, process are ran\n";
	cout << "as soon as they arrive if they can. If not they are added to a\n";
	cout << "queue and are executed once the other process finishes. If \n";
	cout << "nothing is in the queue the system is idle.\n\n";

	for (int i = 0; length != num ; i++)
	{
		for (int j = 0; j < num; j++)
		{
			
			// If Arrival is at current time add to queue
			if (table[j][0] == i)
			{
				pqueue.push(j);
				length++;
				//cout << "Added " << j << " to queue.\n";
			}
		}
	}
	
	int i = 0;

	// Display when processes are running and when they finish
	while (!pqueue.empty())
	{
		currentProcess = pqueue.front();
		// If the next process in the queue hasn't arrived yet idle till it has arrived
		if ( table[currentProcess][0] > i)
		{
			cout << "Idle from time " << i << " to " << table[currentProcess][0] << "\n\n";
			i = table[currentProcess][0];
		}
		// Print the starting time of a process
		cout << "Starting to run p" << currentProcess << " at time " << i << endl;
		i += table[currentProcess][1];
		// Output when a process finishes
		cout << "Finishing p" << currentProcess << " at time " << i;
		cout << "\n\n";
		// After the process has finished remove it from the queue
		pqueue.pop();
	}

}

/************************************************************************
*   Function: void SJFSimulation(int table[][3], int totalBurst, int num)
*   Description: This function outputs how the SJF simulation works and 
* 	also outputs each step as processes are ran. It outputs when a process
* 	starts and finishes and will also output if the system is idle. 
************************************************************************/
void SJFSimulation(int table[][3], int totalBurst, int num)
{
	queue<int> pqueue;
	int tableCopy[num][3]; // copy of inital table (to not destroy it)
	int currentProcess;
	int smallestA; //Used for smallest Arrival time
	int smallestB; //Used for smallest Burst
	int smallestIndex = 0; //Keeps track of smallest index
	int length = 0;

	// Print output explaining FCFS
	cout << "\nBeginning simulation...\n";
	cout << "In Shortest Job First process scheduling, the processes that have\n";
	cout << "the smallest burst and have arrived are executed first. If a\n";
	cout << "process is already running they are put in a queue and will be\n";
	cout << "executed once the other process has finished.\n\n"; 


	// Make a copy of the original table to clobber
	for (int i = 0; i < num; i++)
	{
		tableCopy[i][0] = table[i][0];
		tableCopy[i][1] = table[i][1];
	}

	//Loop through the table and find the processes with smallest arrival and burst
	for (int i = 0; length != num ; i++)
	{
		// Set smallest to p0
		smallestA = tableCopy[0][0];
		smallestB = tableCopy[0][1];
		smallestIndex = 0;
		for (int j = 0; j < num; j++)
		{
			// Find smallest arrival and burst time process
			if (tableCopy[j][0] <= smallestA && tableCopy[j][1] <= smallestB)
			{
				smallestA = tableCopy[j][0];
				smallestB = tableCopy[j][1];
				smallestIndex = j;
			}
		}
		// Push the process number with the smallest arrival and burst
		pqueue.push(smallestIndex);
		//cout << "Added " << smallestIndex << " to queue.\n";
		//cout << "Smallest found is p" << smallestIndex << endl;
		// Remove the added process from the table (clobber the data)
		tableCopy[smallestIndex][0] = INT_MAX;
		tableCopy[smallestIndex][1] = INT_MAX;
		length++;
	}

	int i = 0;
	
	// Display when processes are running and when they finish	
	while (!pqueue.empty())
	{
		currentProcess = pqueue.front();
		// If the next process in the queue hasn't arrived yet idle till it has arrived
		if ( table[currentProcess][0] > i)
		{
			cout << "Idle from time " << i << " to " << table[currentProcess][0] << "\n\n";
			i = table[currentProcess][0];
		}
		// Print the starting time of a process
		cout << "Starting to run p" << currentProcess << " at time " << i << endl;
		i += table[currentProcess][1];
		// Output when a process finishes
		cout << "Finishing p" << currentProcess << " at time " << i;
		cout << "\n\n";
		// After the process has finished remove it from the queue
		pqueue.pop();
	}
}

/************************************************************************
*   Function: void RRSimulation(int table[][3], 
								int totalBurst, int num, int quantum)
*   Description: This function outputs how the RR simulation works and 
* 	also outputs each step as processes are ran. It outputs when a process
* 	starts, stops, and finishes and will also output if the system is idle.
************************************************************************/
void RRSimulation(int table[][3], int totalBurst, int num, int quantum)
{
	queue<int> pqueue;
	int currentProcess;
	int length = 0;

	// Print output explaining RR
	cout << "\nBeginning simulation...\n";
	cout << "In Round Robin process scheduling a quantum is added, which is \n";
	cout << "a block of time that a process will run before starting the \n";
	cout << "next process in the queue. If there are no processes that have \n";
	cout << "arrived yet the system is idle for that quantum. Round Robin \n";
	cout << "trys to make sure every process gets a reasonable response time.\n";
	cout << "Please note each block of text is a quantum.\n\n";

	// Build the inital queue the same as first come first serve
	for (int i = 0; length != num ; i++)
	{
		for (int j = 0; j < num; j++)
		{
			
			// If Arrival is at current time add to queue
			if (table[j][0] == i)
			{
				pqueue.push(j);
				length++;
				//cout << "Added " << j << " to queue.\n";
			}
		}
	}

	int i = 0;
	int temp = 0;
	// Display when processes are running and when they finish	
	while (!pqueue.empty())
	{
		currentProcess = pqueue.front();
		// If the next process in the queue hasn't arrived yet idle till it has arrived
		if ( table[currentProcess][0] > i)
		{
			cout << "Idle from time " << i << " to " << i + quantum << "\n\n";
			//Jump forward a quantum
			i += quantum;
			continue;
		}
		// Print the starting time of a process
		cout << "Starting to run p" << currentProcess << " at time " << i << endl;
		i += quantum;
		// Check to see if process is done at the end of quantum if not display stopped
		if (table[currentProcess][1] > 0 && table[currentProcess][1] - quantum > 0)
		{
			cout << "Stopping p" << currentProcess << " at time " << i;
			cout << "\n\n";
		}
		// If process is finished display that it is finishing
		else
		{
			//Check to see if there is remaining time in the quantum after the process has finished
			if (table[currentProcess][1] - quantum == 0)
				cout << "Finishing p" << currentProcess << " at time " << i;
			//If there is time remaing display the remaining time idle for the quantum
			else
			{
				cout << "Finishing p" << currentProcess << " at time " << ((table[currentProcess][1] - quantum) + i) << endl;
				cout << "Idle from time " << ((table[currentProcess][1] - quantum) + i) << " to " << ((table[currentProcess][1] - quantum) + i) + (quantum - table[currentProcess][1]);
			}
			cout << "\n\n";
			pqueue.pop();
			continue;
		}
		if (i % quantum == 0)
		{
			//Send the current process after a quantum to the back of the queue
			temp = pqueue.front();
			pqueue.pop();
			table[currentProcess][1] -= quantum;
			if (table[currentProcess][1] > 0)
			{
				pqueue.push(temp);
			}
			currentProcess = pqueue.front();
		}

	}
}

