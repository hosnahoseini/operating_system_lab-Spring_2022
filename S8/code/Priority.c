#include<stdio.h>
#include<stdlib.h>

struct Process{

  int pid;
  int bt;
  int wt;
  int tt;
  int priority;
};

struct Process * p;


void swap(int i , int j);
 
int main() {


  int n;
 
  printf("Enter Total number of Processes:");
  scanf("%d",&n);
  p = (struct Process*) malloc(n*sizeof(struct Process));


  for(int i  = 1; i <= n; i++){
  	p[i-1].pid = i;
    printf("P%d:\n", i);
    printf("Burst Time: ");
    scanf("%d",&p[i-1].bt);
    printf("Priority: ");
    scanf("%d",&p[i-1].priority);
    p[i-1].wt = 0;
    p[i-1].tt = 0;
  }

  for (int i = 0; i < n; ++i)
    for (int j = i; j < n; ++j){
      
      if (p[i].priority > p[j].priority)
          swap(i,j);
      else if (p[i].priority == p[j].priority && p[i].bt < p[j].bt)
          swap(i,j);
    }

  p[0].wt = 0;
  p[0].tt = p[0].bt;

	// calculating waiting time
	for (int i = 1; i < n ; i++)
		p[i].wt = p[i-1].wt + p[i-1].bt;
	

	for (int i = 0; i < n ; i++)
		p[i].tt = p[i].bt + p[i].wt;

	printf("Processes \t Burst Time \t Waiting Time \t Turn-Around Time\n");
	int total_wt = 0, total_tat = 0;
	for (int i = 0 ; i < n ; i++)
	{
		total_wt = total_wt + p[i].wt;
		total_tat = total_tat + p[i].tt;
		printf("%d\t\t\t%d\t\t%d\t\t%d\n", p[i].pid, p[i].bt, p[i].wt, p[i].tt);
	}

	printf("Average waiting time = %f", (float)total_wt / (float)n);
	printf("\nAverage turn around time = %f\n", (float)total_tat / (float)n);
  
  return 0;
}

void swap(int i, int j){
   
    int temp_id = p[i].pid;
    int temp_bt = p[i].bt;
    int temp_priority = p[i].priority;
    p[i].pid = p[j].pid;
    p[i].bt = p[j].bt;
    p[i].priority = p[j].priority;
    p[j].pid = temp_id;
    p[j].bt = temp_bt;
    p[j].priority = temp_priority;
}

