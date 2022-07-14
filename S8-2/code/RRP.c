#include<stdio.h>
#include<stdlib.h>

struct Process{

  int pid;
  int bt;
  int wt;
  int tt;
  int at; //arrival time
  int nt; //needed time
  int priority;
};

struct Process * p;

void swap(int i, int j){
   
    int temp_id = p[i].pid;
    int temp_bt = p[i].bt;
    int temp_wt = p[i].wt;
    int temp_tt = p[i].tt;
    int temp_at = p[i].at;
    int temp_nt = p[i].nt;
    int temp_priority = p[i].priority;

    p[i].pid = p[j].pid;
    p[i].bt = p[j].bt;
    p[i].wt = p[j].wt;
    p[i].tt = p[j].tt;
    p[i].at = p[j].at;
    p[i].nt = p[j].nt;
    p[i].priority = p[j].priority;

    p[j].pid = temp_id;
    p[j].bt = temp_bt;
    p[j].wt = temp_wt;
    p[j].tt = temp_tt;
    p[j].at = temp_at;
    p[j].nt = temp_nt;
    p[j].priority = temp_priority;
}

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

  for(int i  = 1; i <= n; i++){
  	p[i-1].pid = i;
    printf("P%d:\n", i);
    printf("Burst Time: ");
    scanf("%d",&p[i-1].bt);
    printf("Priority: ");
    scanf("%d",&p[i-1].priority);
    p[i-1].wt = 0;
    p[i-1].tt = 0;
    p[i-1].nt = p[i-1].bt;
    p[i-1].at = 0;

  }

  printf("Enter the Time Quantum(q):");
  scanf("%d",&quantum);
  printf("\nProcess \t Turnaround Time \t Waiting Time\n\n");

  time = 0;
  i = 0;
      
    // sort by priority
    for (int k = 0; k < n; ++k)
        for (int j = k; j < n; ++j){
            if (p[k].priority > p[j].priority)
                swap(k,j);
            else if (p[k].priority == p[j].priority && p[k].bt < p[j].bt)
                swap(k,j);
        }
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

      printf("P%d\t\t\t%d\t\t%d\n", p[i].pid, p[i].tt, p[i].wt);
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