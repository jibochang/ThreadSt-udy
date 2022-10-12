#define THREAD_NUM 150

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* func(void* arg){
	printf("This is child thread!:%d\n",*(int*)arg);
	sleep(20);
	pthread_exit("thread exited!");

}

int main(){
	pthread_t tid[THREAD_NUM];
	void* retv;
	for(int i = 0;i < THREAD_NUM;i++){
		pthread_create(tid+i,NULL,func,(void*)&i);
	}

	for(int i = 0;i < THREAD_NUM;i++){
		pthread_join(tid[i],&retv);
		printf("thread ret = %s\n",(char*)retv);
	}
	while(1){
		sleep(1);
	}
	return 0;
}
