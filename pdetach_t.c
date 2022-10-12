#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* func(void* arg){
	pthread_detach(pthread_self());
	printf("This is child thread!:%d\n",*(int*)arg);
	sleep(2);
	pthread_exit("thread exited!");

}

int main(){
	pthread_t tid[5];
	void* retv;
	for(int i = 0;i < 5;i++){
		pthread_create(tid+i,NULL,func,(void*)&i);
		sleep(1);
	}

	return 0;
}
