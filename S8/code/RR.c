#include<stdio.h>
#include<stdlib.h>

struct Process{

  int pid;
  int bt;
  int wt;
  int tt;
  int at; //arrival time
  int nt; //needed time
};

struct Process * p;
int main()
{
 
  int n = 0; //total number of process
  p = (struct Process*) malloc(n*sizeof(struct Process));
  int i =0;
  int flag = 0;
  int time = 0;
  int remaining_processes = 0;
  int quantum = 0;
  int total_wt = 0;
  int total_tat = 0;


  printf("Enter number of Processes:");
  scanf("%d",&n);
  p = (struct Process*) malloc(n*sizeof(struct Process));

  remaining_processes = n;

  for(i = 0;i < n;i++)
  {
    printf("P%d: ",i + 1);
    p[i].pid = i + 1;
    p[i].at = 0;
    scanf("%d",&p[i].bt);
    p[i].nt = p[i].bt;
  }

  printf("Enter the Time Quantum(q):");
  scanf("%d",&quantum);
  printf("\nProcess \t Turnaround Time \t Waiting Time\n\n");

  time = 0;
  i = 0;
  while(remaining_processes > 0)
  {
    if(p[i].nt <= quantum && p[i].nt > 0)
    {
      time += p[i].nt;
      p[i].nt = 0;
      flag = 1;
    }
    else if(p[i].nt > 0)
    {
      p[i].nt -= quantum;
      time += quantum;
      printf("P%d\n", i + 1);
    }
    if(p[i].nt == 0 && flag == 1)
    {
      remaining_processes--;
      p[i].tt = time - p[i].at;
      p[i].wt = time - p[i].at - p[i].bt;
      total_wt += p[i].wt;
      total_tat += p[i].tt;

      printf("P%d\t\t\t%d\t\t%d\n", i + 1, p[i].tt, p[i].wt);
      flag=0;
    }

    if(i == n - 1)
      i = 0;

    else if(p[i+1].at <= time)
      i ++;
    
    else
      i = 0;
    
  }

    printf("Average waiting time = %f", (float)total_wt / (float)n);
	printf("\nAverage turn around time = %f\n", (float)total_tat / (float)n);
  
  return 0;
}