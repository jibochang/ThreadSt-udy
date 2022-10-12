#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void cleanup(void* arg){
	printf("clean up,arg=%s\n",(char*)arg);
}

void* func(void* arg){
	printf("This is child thread!\n");
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
	pthread_cleanup_push(cleanup,"abcde");
	//while(1){
		sleep(1);
	//}
	pthread_cancel(pthread_self());
	printf("Should not print\n");

	pthread_exit("thread exited!");
	pthread_cleanup_pop(1);
	printf("Not !!\n");
	pthread_exit("thread exited!");
}

int main(){
	pthread_t tid;
	pthread_create(&tid,NULL,func,NULL);
	sleep(2);
	//pthread_cancel(tid);
	//pthread_join(tid,NULL);
	printf("Thread ret\n");
	while(1){
		sleep(1);
	}
	return 0;
}
