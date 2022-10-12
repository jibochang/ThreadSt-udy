#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;

FILE* fp;

void* func1(void* arg){
	pthread_detach(pthread_self());
	printf("This is thread1!\n");
	while(1){
		pthread_mutex_lock(&mutex);
		sleep(1);
		printf("%s got 1 mutex\n",(char*)arg);
		pthread_mutex_lock(&mutex2);
		sleep(1);
		printf("%s got 2 mutexs\n",(char*)arg);

		pthread_mutex_unlock(&mutex2);
		pthread_mutex_unlock(&mutex);
		sleep(10);
	}
	pthread_exit("thread1 exited!");

}

void* func2(void* arg){
	pthread_detach(pthread_self());
	printf("This is thread2!\n");
        while(1){
		sleep(3);
		pthread_mutex_lock(&mutex2);
		sleep(1);
		printf("%s got 1 mutex2\n",(char*)arg);
		pthread_mutex_lock(&mutex);
		sleep(1);
		printf("%s got 2 mutexs\n",(char*)arg);

		pthread_mutex_unlock(&mutex);
		pthread_mutex_unlock(&mutex2);
		sleep(7);
        }
	pthread_exit("thread2 exited!");
}

int main(){
	pthread_t tid1,tid2;
	char t1[] = "Thread1";
	char t2[] = "Thread2";
	
	pthread_create(&tid1,NULL,func1,(void*)t1);
	pthread_create(&tid2,NULL,func2,(void*)t2);
	while(1){
		sleep(1);
	}
	return 0;
}
