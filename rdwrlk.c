#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>

pthread_rwlock_t rwlock;

FILE* fp;

void* func1(void* arg){
	pthread_detach(pthread_self());
	printf("This is thread1!\n");
	char str[] = "This is thread1!\n";
	int i = 0;
	while(1){
		pthread_rwlock_wrlock(&rwlock);
		while(i<strlen(str)){
			fputc(str[i],fp);
			usleep(1);
			i++;
		}
		pthread_rwlock_unlock(&rwlock);
		i = 0;
		//usleep(1);
		usleep(1000);
	}
	pthread_exit("thread1 exited!");

}

void* func2(void* arg){
	pthread_detach(pthread_self());
	printf("This is thread2!\n");
	char str[] = "This is thread2!\n";
	int i = 0;
        while(1){
		pthread_rwlock_wrlock(&rwlock);
                while(i<strlen(str)){
                        fputc(str[i],fp);
                        usleep(1);
                        i++;
                }
		pthread_rwlock_unlock(&rwlock);
                i = 0;
                usleep(1000);
        }
	pthread_exit("thread2 exited!");
}

void* func3(void* arg){
	pthread_detach(pthread_self());
	printf("read thread\n");
	char buf[32] = {0};
	while(1){
		rewind(fp);
		pthread_rwlock_rdlock(&rwlock);
		fgets(buf,32,fp);
		printf("rd=%s\n",buf);
		pthread_rwlock_unlock(&rwlock);
		sleep(1);
	}
	pthread_exit("thread3 exited");

}

int main(){
	pthread_t tid1,tid2,tid3,tid4;
	fp = fopen("2.txt","a+");
	if(fp == NULL){
		perror("fopen");
		return 0;
	}
	
	pthread_rwlock_init(&rwlock,NULL);

	pthread_create(&tid1,NULL,func3,NULL);
	pthread_create(&tid2,NULL,func1,NULL);
	pthread_create(&tid3,NULL,func2,NULL);
	//pthread_create(&tid4,NULL,func3,2);
	while(1){
		sleep(1);
	}
	return 0;
}
