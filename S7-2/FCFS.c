#include<stdio.h>

// Function to find the waiting time for all
// processes
void findWaitingTime(int processes[], int n, int bt[],
								int wt[], int at[])
{
	int service_time[n];
	service_time[0] = at[0];
	wt[0] = 0;

	// calculating waiting time
	for (int i = 1; i < n ; i++)
	{
		// Add burst time of previous processes
		service_time[i] = service_time[i-1] + bt[i-1];

		// Find waiting time for current process =
		// sum - at[i]
		wt[i] = service_time[i] - at[i];

		// If waiting time for a process is in negative
		// that means it is already in the ready queue
		// before CPU becomes idle so its waiting time is 0
		if (wt[i] < 0)
			wt[i] = 0;
	}
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n, int bt[],
									int wt[], int tat[])
{
	// Calculating turnaround time by adding bt[i] + wt[i]
	for (int i = 0; i < n ; i++)
		tat[i] = bt[i] + wt[i];
}

// Function to calculate average waiting and turn-around
// times.
void findavgTime(int processes[], int n, int bt[], int at[])
{
	int wt[n], tat[n];

	// Function to find waiting time of all processes
	findWaitingTime(processes, n, bt, wt, at);

	// Function to find turn around time for all processes
	findTurnAroundTime(processes, n, bt, wt, tat);

	// Display processes along with all details
	printf("Processes \t Burst Time \t Arrival Time \t Waiting Time \t Turn-Around Time \t Completion Time \n");
	int total_wt = 0, total_tat = 0;
	for (int i = 0 ; i < n ; i++)
	{
		total_wt = total_wt + wt[i];
		total_tat = total_tat + tat[i];
		int compl_time = tat[i] + at[i];
		printf("%d\t\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d\n", i+1, bt[i], at[i], wt[i], tat[i], compl_time);
	}

	printf("Average waiting time = %f", (float)total_wt / (float)n);
	printf("\nAverage turn around time = %f", (float)total_tat / (float)n);
}

// Driver code
int main()
{
	// Process id's
	int processes[] = {1, 2, 3, 4, 5, 6, 7, 8};
	int n = sizeof processes / sizeof processes[0];

	// Burst time of all processes
	int burst_time[] = {10, 6, 2, 20, 10, 5, 5, 10};

	// Arrival time of all processes
	int arrival_time[] = {0, 3, 5, 9, 11, 29, 39, 50};

    int preemptine[] = {1, 1, 1, 1, 0, 1, 0, 1, 0};

	findavgTime(processes, n, burst_time, arrival_time);

	return 0;
}
