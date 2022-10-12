#define POOL_NUM 10

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct Task{
	void* (*func)(void* arg);
	void* arg;
	struct Task* next;

}Task;

typedef struct ThreadPool{
	pthread_mutex_t taskLock;
	pthread_cond_t newTask;

	pthread_t tid[POOL_NUM];
	Task* queue_head;
	int taskNum;

}ThreadPool;

ThreadPool* pool = NULL;

void* workThread(void* arg){
	while(1){
		pthread_mutex_lock(&pool->taskLock);
		pthread_cond_wait(&pool->newTask,&pool->taskLock);

		Task* ptask = pool->queue_head;
		pool->queue_head = pool->queue_head->next;


		pthread_mutex_unlock(&pool->taskLock);

		ptask->func(ptask->arg);
		pool->taskNum--;
	}
}

void* realwork(void* arg){
	printf("This is %d work\n",(int)arg);
}

void pool_add_task(int arg){
	Task* newTask;

	pthread_mutex_lock(&pool->taskLock);
	
	while(pool->taskNum >= POOL_NUM){
		pthread_mutex_unlock(&pool->taskLock);
		usleep(10000);
		pthread_mutex_lock(&pool->taskLock);
	}
	
	pthread_mutex_unlock(&pool->taskLock);
	
	newTask = malloc(sizeof(Task));
	newTask->func = realwork;
	newTask->arg =(void*)arg;

	pthread_mutex_lock(&pool->taskLock);
	
	Task* member = pool->queue_head;
	if(member == NULL){
		pool->queue_head = newTask;
	}else{
		while(member->next != NULL)
			member = member->next;
		member->next = newTask;
	}
	pool->taskNum++;
	pthread_cond_signal(&pool->newTask);

	pthread_mutex_unlock(&pool->taskLock);
}

void pool_init(){
	pool = malloc(sizeof(ThreadPool));
	pthread_mutex_init(&pool->taskLock,NULL);
	pthread_cond_init(&pool->newTask,NULL);
	pool->queue_head = NULL;
	pool->taskNum = 0;

	for(int i = 0;i < POOL_NUM;i++){
		pthread_create(&pool->tid[i],NULL,workThread,NULL);
	}

	
}

void pool_destroy(){
	Task* head;
	while(pool->queue_head != NULL){
		head = pool->queue_head;
		pool->queue_head = pool->queue_head->next;
		free(head);
	}

	pthread_mutex_destroy(&pool->taskLock);
	pthread_cond_destroy(&pool->newTask);
	free(pool);
}

int main(){
	pool_init();
	sleep(1);
	for(int i = 0;i < 20;i++){
		pool_add_task(i);
	}
	sleep(2);
	pool_destroy();
	return 0;
}
