#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>


int main()
{
	
	key_t key = 2525;

	// shmget returns an identifier in shmid
	int shmid = shmget(key, sizeof(int), 0666|IPC_CREAT);

	// shmat to attach to shared memory
	int *count = (int*) shmat(shmid, (void*)0, 0);
    *count = 0;

    int n1 = fork();
    int n2 = fork();


    if (n1 != 0 && n2 != 0){
	    while(*count < 10){
            (*count) ++;
            printf("Writer:\tPID: %d\tcount: %d\n", getpid(), *count);
            usleep(500);
	    }
        wait(NULL);
        wait(NULL);
        wait(NULL);
    }
    else if (n1 == 0 || n2 == 0){
        while(*count < 10){
            int current_pid = getpid();
                printf("Reader:\tPID: %d\tcount: %d\n", current_pid, *count);
        }
    }

}