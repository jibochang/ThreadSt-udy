#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

FILE* fp;

void* func1(void* arg){
	pthread_detach(pthread_self());
	printf("This is thread1!\n");
	char str[] = "This is thread1!\n";
	int i = 0;
	while(1){
		pthread_mutex_lock(&mutex);
		while(i<strlen(str)){
			fputc(str[i],fp);
			usleep(1);
			i++;
		}
		pthread_mutex_unlock(&mutex);
		i = 0;
		usleep(1);
	}
	pthread_exit("thread1 exited!");

}

void* func2(void* arg){
	pthread_detach(pthread_self());
	printf("This is thread2!\n");
	char str[] = "This is thread2!\n";
	int i = 0;
        while(1){
		pthread_mutex_lock(&mutex);
                while(i<strlen(str)){
                        fputc(str[i],fp);
                        usleep(1);
                        i++;
                }
		pthread_mutex_unlock(&mutex);
                i = 0;
                usleep(1);
        }
	pthread_exit("thread2 exited!");
}

int main(){
	pthread_t tid1,tid2;
	fp = fopen("1.txt","a+");
	if(fp == NULL){
		perror("fopen");
		return 0;
	}
	pthread_create(&tid1,NULL,func1,NULL);
	pthread_create(&tid2,NULL,func2,NULL);
	while(1){
		sleep(1);
	}
	return 0;
}
