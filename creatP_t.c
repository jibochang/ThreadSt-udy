#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* testThread(void* arg){
	printf("This is testThread\npid=%d\nself_tid=%lu\n",getpid(),pthread_self());
	printf("Input num is : %d\n",*((int*)arg));
	pthread_exit(NULL);
	printf("After pthread_exit\n");

}

int main(){
	pthread_t tid;
	int arg = 5;
	int ret = pthread_create(&tid,NULL,testThread,(void*)&arg);
	printf("This is main thread\npid=%d\ntid=%lu\n",getpid(),tid);
	sleep(1);
	return 0;
}
