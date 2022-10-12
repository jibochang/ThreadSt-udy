#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

pthread_cond_t hasTaxi = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct taxi{
	int num;
	struct taxi* next;
}taxi;

taxi* Head = NULL;

void* taxiarv(void* arg){
	printf("Taxi arrived thread!\n");
	pthread_detach(pthread_self());
	taxi* tx;
	int i = 1;
	while(1){
		tx = malloc(sizeof(taxi));
		tx->num = i++;
		printf("taxi %d is coming\n",tx->num);
		pthread_mutex_lock(&lock);
		
		tx->next = Head;
		Head = tx;
		//pthread_cond_signal(&hasTaxi);
		pthread_cond_broadcast(&hasTaxi);


		pthread_mutex_unlock(&lock);
		sleep(1);
	}

	pthread_exit(0);
}

void* takeTaxi(void* arg){
	printf("Take taxi thread!\n");
	pthread_detach(pthread_self());
	taxi* tx;
	while(1){
		pthread_mutex_lock(&lock);

		while(Head == NULL){
			pthread_cond_wait(&hasTaxi,&lock);
		}

		tx = Head;
		Head = tx->next;
		printf("%d taxi has been taken by %d\n",tx->num,(int)arg);
		free(tx);

		pthread_mutex_unlock(&lock);
	}
	pthread_exit(0);
}

int main(){
	pthread_t tid1,tid2,tid3,tid4;

	pthread_create(&tid1,NULL,taxiarv,NULL);
	//sleep(5);
	pthread_create(&tid2,NULL,takeTaxi,(void*)1);
	pthread_create(&tid3,NULL,takeTaxi,(void*)2);
	pthread_create(&tid4,NULL,takeTaxi,(void*)3);

	while(1){
		sleep(1);
	}
	return 0;
}
