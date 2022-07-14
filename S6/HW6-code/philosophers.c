#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

void *handle_philosopher(void * i);
void think(int philosopher);
void eat(int philosopher);
void finish(int philosopher);
void pickup(int philosopher);
void putdown(int philosopher);

sem_t pick_up;
pthread_t philosopher[5];
pthread_mutex_t chopsticks[5];
int count[5];

int main(){

	sem_init(&pick_up, 0 , 1);

	for (int i = 0; i < 5; ++i)
	{
		if (pthread_mutex_init(&chopsticks[i], NULL))
		{
			printf("Mutex Initialize Failed\n");
			return 0;
		}
	}
	for (int i = 0; i < 5; ++i)
	{
		pthread_create(&philosopher[i], NULL, handle_philosopher, (void *)i);
	}
	for (int i = 0; i < 5; ++i)
	{
		pthread_join(philosopher[i], NULL);
	}
}

void *handle_philosopher (void *i){

	int id = (int)(long) i;

	count[id] = 1;
	while(1){
		
		//think
		think(id);
		
		//pickup
		sem_wait(&pick_up);
		pickup(id);
		sem_post(&pick_up);

		//eat
		eat(id);

		//finish eating
		finish(id);
		
		//putdown
		putdown(id);


		count[id]++;
	}
}

void pickup(int philosopher){
	pthread_mutex_lock(&chopsticks[philosopher]);
	pthread_mutex_lock(&chopsticks[(philosopher+1)%5]);
}

void putdown(int philosopher){
	pthread_mutex_unlock(&chopsticks[philosopher]);
	pthread_mutex_unlock(&chopsticks[(philosopher+1)%5]);
}

void think(int philosopher){
	printf("philosopher %d is thinking\n", philosopher);
	sleep(2);
}

void eat(int philosopher){
	printf("philosopher %d is eating with chopsticks[%d] and chopsticks[%d]\n", philosopher, philosopher, (philosopher+1)%5);
	sleep(2);

}

void finish(int philosopher){
	printf("philosopher %d finished eating\n", philosopher);
}