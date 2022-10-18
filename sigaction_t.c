#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef void (*sighander_t)(int);

sighander_t oldact;

void handler(int sig){
	if(sig==SIGINT){
		printf("\nI catch thr SIGINT!\n");
	}else if(sig==SIGALRM){
		printf("Timer!\n");
		alarm(1);
	}
	//signal(SIGINT,oldact);
}

int main(){
	struct sigaction act;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT,&act,NULL);
	alarm(1);
	sigaction(SIGALRM,&act,NULL);

	//oldact = signal(SIGINT,handler);

	while(1){
		sleep(1);
	}
}
