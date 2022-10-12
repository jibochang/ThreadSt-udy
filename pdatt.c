#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* func(void* arg){
	printf("This is child thread!:%d\n",*(int*)arg);
	sleep(2);
	pthread_exit("thread exited!");

}

int main(){
	pthread_t tid[5];
	void* retv;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	for(int i = 0;i < 5;i++){
		pthread_create(tid+i,&attr,func,(void*)&i);
		sleep(1);
	}

	return 0;
}
