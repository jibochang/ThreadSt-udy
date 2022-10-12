#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* func(void* arg){
	int time = 0;
	printf("This is child thread!\n");
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
	while(1){
		if(time == 8)
			pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
		printf("thread:%d\n",time);
		sleep(1);
		pthread_testcancel();
		time++;
	}
	pthread_exit("thread exited!");

}

int main(){
	pthread_t tid;
	//void* retv;
	pthread_create(&tid,NULL,func,NULL);
	sleep(3);
	pthread_cancel(tid);
	pthread_join(tid,NULL);
	printf("Thread ret\n");
	while(1){
		sleep(1);
	}
	return 0;
}
