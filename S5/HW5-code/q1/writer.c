#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
  
int main()
{
    
    key_t key = 2525;;
  
    // shmget returns an identifier in shmid
    int shmid = shmget(key, sizeof(int) * 2, 0666|IPC_CREAT);
  
    // shmat to attach to shared memory
    int *nums = (int*) shmat(shmid,(void*)0,0);
  
    printf("Write Data : ");
    scanf("%d", &nums[0]);

    printf("Write Data : ");
    scanf("%d", &nums[1]);
  
    printf("Data written in memory: %d, %d\n", nums[0], nums[1]);
      
    //detach from shared memory 
    shmdt(nums);
  
    return 0;
}