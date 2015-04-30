#include "header.h"

void MainMenu()
{
	int selection = 0;
	system("clear");
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

void RoundRobin()
{
	int procNumber = 0;
	cout << "You selected: Round Robin" << endl;
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

void FirstComeFirstServe()
{
	int procNumber = 0;
	cout << "You selected: FirstComeFirstServe" << endl;
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

void ShortestJobFirst()
{
	int procNumber = 0;
	cout << "You selected: Shortet Job First" << endl;
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

void setProcessesRR(int num)
{
	int procArray[num][3];
	int arrival;
	int burst;
	int quantum;
	int totalBurst = 0;
	cout << "Please enter a quantum between 1 and 20: ";
	cin >> quantum;
	if (quantum < 0 || quantum > 20)
	{
		cout << "Invalid Quantum\n";
		return;
	}
	for(int i = 0; i < num; i++)
	{
		cout << "Please input an arrival time for process " << i << ": ";
		cin >> arrival;
		if (arrival < 0)
		{
			cout << "Invalid input\n";
			return;
		}
		cout << "Please input a burst time for process " << i << ": ";
		cin >> burst;
		if (burst < 1)
		{
			cout << "Invalid input\n";
			return;
		}
		procArray[i][0] = arrival;
		procArray[i][1] = burst;
	}


	cout << "\nProcess table\n";
	cout << "Process		Arrival		Burst\n";
	for (int i = 0; i < num; i++)
	{
		cout << "p" << i << "		";
		cout << procArray[i][0] <<  "		";
		cout << procArray[i][1] << endl;
		totalBurst += procArray[i][1];
	}
	
	RRSimulation(procArray, totalBurst, num, quantum);
}

void setProcessesFCFS(int num)
{
	int procArray[num][3];
	int arrival;
	int burst;
	int totalBurst = 0;
	for(int i = 0; i < num; i++)
	{
		cout << "Please input an arrival time for process " << i << ": ";
		cin >> arrival;
		if (arrival < 0)
		{
			cout << "Invalid input\n";
			return;
		}
		cout << "Please input a burst time for process " << i << ": ";
		cin >> burst;
		if (burst < 1)
		{
			cout << "Invalid input\n";
			return;
		}
		procArray[i][0] = arrival;
		procArray[i][1] = burst;
	}


	cout << "\nProcess table\n";
	cout << "Process		Arrival		Burst\n";
	for (int i = 0; i < num; i++)
	{
		cout << "p" << i << "		";
		cout << procArray[i][0] <<  "		";
		cout << procArray[i][1] << endl;
		totalBurst += procArray[i][1];
	}
	
	FCFSSimulation(procArray, totalBurst, num);
}

void setProcessesSJF(int num)
{
	int procArray[num][3];
	int arrival;
	int burst;
	int totalBurst = 0;
	for(int i = 0; i < num; i++)
	{
		cout << "Please input an arrival time for process " << i << ": ";
		cin >> arrival;
		if (arrival < 0)
		{
			cout << "Invalid input\n";
			return;
		}
		cout << "Please input a burst time for process " << i << ": ";
		cin >> burst;
		if (burst < 1)
		{
			cout << "Invalid input\n";
			return;
		}
		procArray[i][0] = arrival;
		procArray[i][1] = burst;
	}


	cout << "\nProcess table\n";
	cout << "Process		Arrival		Burst\n";
	for (int i = 0; i < num; i++)
	{
		cout << "p" << i << "		";
		cout << procArray[i][0] <<  "		";
		cout << procArray[i][1] << endl;
		totalBurst += procArray[i][1];
	}
	
	SJFSimulation(procArray, totalBurst, num);
}

void FCFSSimulation(int table[][3], int totalBurst, int num)
{
	queue<int> pqueue;
	int currentProcess;
	int length = 0;

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

	while (!pqueue.empty())
	{
		currentProcess = pqueue.front();
		if ( table[currentProcess][0] > i)
		{
			cout << "Idle from time " << i << " to " << table[currentProcess][0] << "\n\n";
			i = table[currentProcess][0];
		}
		cout << "Starting to run p" << currentProcess << " at time " << i << endl;
		i += table[currentProcess][1];
		cout << "Finishing p" << currentProcess << " at time " << i;
		cout << "\n\n";
		pqueue.pop();
	}

}

void SJFSimulation(int table[][3], int totalBurst, int num)
{
	queue<int> pqueue;
	int tableCopy[num][3];
	int currentProcess;
	int smallestA;
	int smallestB;
	int smallestIndex = 0;
	int length = 0;
	cout << "\nBeginning simulation...\n";
	cout << "In Shortest Job First process scheduling, the processes that have\n";
	cout << "the smallest burst and have arrived are executed first. If a\n";
	cout << "process is already running they are put in a queue and will be\n";
	cout << "executed once the other process has finished.\n\n"; 


	for (int i = 0; i < num; i++)
	{
		tableCopy[i][0] = table[i][0];
		tableCopy[i][1] = table[i][1];
	}

	for (int i = 0; length != num ; i++)
	{
		// Set smallest to p0
		smallestA = tableCopy[0][0];
		smallestB = tableCopy[0][1];
		smallestIndex = 0;
		for (int j = 0; j < num; j++)
		{
			// Find smallest arrival and burst and put into queue
			
			if (tableCopy[j][0] <= smallestA && tableCopy[j][1] <= smallestB)
			{
				smallestA = tableCopy[j][0];
				smallestB = tableCopy[j][1];
				smallestIndex = j;
			}
		}
		pqueue.push(smallestIndex);
		//cout << "Added " << smallestIndex << " to queue.\n";
		//cout << "Smallest found is p" << smallestIndex << endl;
		tableCopy[smallestIndex][0] = INT_MAX;
		tableCopy[smallestIndex][1] = INT_MAX;
		length++;
	}

	int i = 0;

	while (!pqueue.empty())
	{
		currentProcess = pqueue.front();
		if ( table[currentProcess][0] > i)
		{
			cout << "Idle from time " << i << " to " << table[currentProcess][0] << "\n\n";
			i = table[currentProcess][0];
		}
		cout << "Starting to run p" << currentProcess << " at time " << i << endl;
		i += table[currentProcess][1];
		cout << "Finishing p" << currentProcess << " at time " << i;
		cout << "\n\n";
		pqueue.pop();
	}
}

void RRSimulation(int table[][3], int totalBurst, int num, int quantum)
{
	queue<int> pqueue;
	int currentProcess;
	int length = 0;

	cout << "\nBeginning simulation...\n";
	cout << "In Round Robin process scheduling...\n\n";

	for (int i = 0; length != num ; i++)
	{
		for (int j = 0; j < num; j++)
		{
			
			// If Arrival is at current time add to queue
			if (table[j][0] == i)
			{
				pqueue.push(j);
				length++;
				cout << "Added " << j << " to queue.\n";
			}
		}
	}

	int i = 0;
	while (!pqueue.empty())
	{
		currentProcess = pqueue.front();
		if (i % quantum == 0)
		{

		}
		if ( table[currentProcess][0] > i)
		{
			cout << "Idle from time " << i << " to " << table[currentProcess][0] << "\n\n";
			i = table[currentProcess][0];
		}
		cout << "Starting to run p" << currentProcess << " at time " << i << endl;
		i += table[currentProcess][1];
		cout << "Finishing p" << currentProcess << " at time " << i;
		cout << "\n\n";
		pqueue.pop();
	}
}

