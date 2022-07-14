#include<stdio.h>
#include <stdlib.h>

struct process
{
    int name;
    int AT,BT,WT,TAT,RT,CT;
};
/*Three queues*/
struct process * Q1;
struct process * Q2;
struct process * Q3;

int n;
void sortByArrival()
{
struct process temp;
int i,j;
for(i=0;i<n;i++)
    {
        for(j=i+1;j<n;j++)
            {
                if(Q1[i].AT>Q1[j].AT)
                    {
                          temp=Q1[i];
                          Q1[i]=Q1[j];
                          Q1[j]=temp;
                    }
            }
    }
}

int main()
{
     int total_WT=0, total_TAT=0;
     int i,j,k=0,r=0,time=0,tq1=8,tq2=16,flag=0;
     char c;
     printf("Enter no of processes:");
     scanf("%d",&n);
     Q1 = (struct process*) malloc(n*sizeof(struct process));
     Q2 = (struct process*) malloc(n*sizeof(struct process));
     Q3 = (struct process*) malloc(n*sizeof(struct process));

     for(i=0;i<n;i++)
     {
         Q1[i].name= i + 1;
         printf("\nEnter the arrival time and burst time of process %d: ",Q1[i].name);
         scanf("%d%d",&Q1[i].AT,&Q1[i].BT);
         Q1[i].RT=Q1[i].BT;/*save burst time in remaining time for each process*/

    }
sortByArrival();
time=Q1[0].AT;
printf("Process in first queue following RR with qt=8");
printf("\nProcess\t\tRT\t\tWT\t\tTAT\t\t");
for(i=0;i<n;i++)
{

  if(Q1[i].RT<=tq1)
  {

       time+=Q1[i].RT;/*from arrival time of first process to completion of this process*/
       Q1[i].RT=0;
       Q1[i].WT=time-Q1[i].AT-Q1[i].BT;/*amount of time process has been waiting in the first queue*/
       Q1[i].TAT=time-Q1[i].AT;/*amount of time to execute the process*/
       printf("\n%d\t\t%d\t\t%d\t\t%d",Q1[i].name,Q1[i].RT,Q1[i].WT,Q1[i].TAT);
       total_TAT += Q1[i].TAT;
       total_WT += Q1[i].WT;

  }
  else/*process moves to queue 2 with qt=16*/
  {
      Q2[k].WT=time;
      time+=tq1;
      Q1[i].RT-=tq1;
      Q2[k].BT=Q1[i].RT;
      Q2[k].RT=Q2[k].BT;
      Q2[k].name=Q1[i].name;
      flag=1;
      printf("\n%d\t\t%d\t\t%d\t\t%d",Q2[k].name,Q2[k].BT,Q2[k].WT,Q2[k].TAT);
      k=k+1;


   }

}
if(flag==1)
 {printf("\nProcess in second queue following RR with qt=16");
  printf("\nProcess\t\tRT\t\tWT\t\tTAT\t\t");
}for(i=0;i<k;i++)
   {
    if(Q2[i].RT<=tq2)
     {
       time+=Q2[i].RT;/*from arrival time of first process +BT of this process*/
       Q2[i].RT=0;
       Q2[i].WT=time-tq1-Q2[i].BT;/*amount of time process has been waiting in the ready queue*/
       Q2[i].TAT=time-Q2[i].AT;/*amount of time to execute the process*/
       printf("\n%d\t\t%d\t\t%d\t\t%d",Q2[i].name,Q2[i].RT,Q2[i].WT,Q2[i].TAT);
       total_TAT += Q2[i].TAT;
       total_WT += Q2[i].WT;

    }
    else/*process moves to queue 3 with FCFS*/
    {
      Q3[r].AT=time;
      time+=tq2;
      Q2[i].RT-=tq2;
      Q3[r].BT=Q2[i].RT;
      Q3[r].RT=Q3[r].BT;
      Q3[r].name=Q2[i].name;
      flag=2;
       printf("\n%d\t\t%d\t\t%d\t\t%d",Q3[r].name,Q3[r].BT,Q3[r].WT,Q3[r].TAT);
      r=r+1;


    }

  }

{if(flag==2)
printf("\nProcess in third queue following FCFS ");
}
for(i=0;i<r;i++)
{
    if(i==0)
            Q3[i].CT=Q3[i].BT+time;
        else
            Q3[i].CT=Q3[i-1].CT+Q3[i].BT;

}

for(i=0;i<r;i++)
    {
        Q3[i].RT=0;
        Q3[i].TAT=Q3[i].CT;
        Q3[i].WT=Q3[i].TAT-Q3[i].BT-tq1-tq2;
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t",Q3[i].name,Q3[i].RT,Q3[i].WT,Q3[i].TAT);
        total_TAT += Q3[i].TAT;
        total_WT += Q3[i].WT;

    }
printf("\n");
printf("Average waiting time = %f", (float)total_WT / (float)n);
printf("\nAverage turn around time = %f\n", (float)total_TAT / (float)n);

}

