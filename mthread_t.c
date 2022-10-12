#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* testThread(void* arg){
	//printf("This is testThread\npid=%d\nself_tid=%lu\n",getpid(),pthread_self());
	//printf("Input num is : %d\n",*((int*)arg));
	int index = *(int*)arg;
	int time = 0;
	while(1){
		printf("%d--thread run for %ds\n",index+1,time);
		time++;
		sleep(1);
	}
	//pthread_exit(NULL);
	printf("After pthread_exit\n");

}

int main(){
	pthread_t tid[5];
	int ret;
	for(int i = 0;i < 5;i++){
		ret = pthread_create(tid+i,NULL,testThread,(void*)&i);
		sleep(1);
	}
	//printf("This is main thread\npid=%d\n",getpid());
	while(1){
		sleep(1);
	}
	return 0;
}
