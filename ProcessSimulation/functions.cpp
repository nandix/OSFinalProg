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
	cout << "Please enter a quantum between 1 and 20: ";
	cin >> quantum;
	if (quantum < 0 || quantum > 20)
	{
		cout << "Invalid Quantum\n";
		return;
	}
	cout << "\nPlease enter values between 0 and 50\n";
	for(int i = 0; i < num; i++)
	{
		cout << "Please input an arrival time for process " << i << ": ";
		cin >> arrival;
		if (arrival < 0 || arrival > 50)
		{
			cout << "Invalid input. Exiting.\n";
			return;
		}
		cout << "Please input a burst time for process " << i << ": ";
		cin >> burst;
		if (burst < 0 || burst > 50)
		{
			cout << "Invalid input. Exiting.\n";
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
	}
	
	cout << "Beginning simulation...\n";
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
		if (arrival < 0 || arrival > 50)
		{
			cout << "Invalid input. Exiting.\n";
			return;
		}
		cout << "Please input a burst time for process " << i << ": ";
		cin >> burst;
		if (burst < 0 || burst > 50)
		{
			cout << "Invalid input. Exiting.\n";
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
	for(int i = 0; i < num; i++)
	{
		cout << "Please input an arrival time for process " << i << ": ";
		cin >> arrival;
		if (arrival < 0 || arrival > 50)
		{
			cout << "Invalid input. Exiting.\n";
			return;
		}
		cout << "Please input a burst time for process " << i << ": ";
		cin >> burst;
		if (burst < 0 || burst > 50)
		{
			cout << "Invalid input. Exiting.\n";
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
	}
	
	cout << "Beginning simulation...\n";
}

void FCFSSimulation(int table[][3], int totalBurst, int num)
{
	queue<int> pqueue;
	int time = 0;
	int currentProcess;
	bool running = false;

	cout << "\nBeginning simulation...\n";
	cout << "In First Come First Serve process scheduling process are ran\n";
	cout << "As soon as they arrive.\n\n";

	for (int i = 0; i <= totalBurst; i++)
	{
		for (int j = 0; j < num; j++)
		{
			
			// If Arrival is at current time add to queue
			if (table[j][0] == i)
			{
				pqueue.push(j);
				//cout << "Added " << j << " to queue.\n";
			}
		}
	}
	
	for (int i = 0; i < totalBurst;)
	{
		if (!pqueue.empty())
		{
			currentProcess = pqueue.front();
			if ( table[currentProcess][0] > i)
			{
				i = table[currentProcess][0];
			}
			cout << "Starting to run p" << currentProcess << " at time " << i << endl;
			i += table[currentProcess][1];
			cout << "Finishing p" << currentProcess << " at time " << i;
			cout << "\n\n";
			pqueue.pop();
		}
	}

}

