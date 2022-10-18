#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef void (*sighander_t)(int);

sighander_t oldact;

void handler(int sig){
	printf("I catch thr SIGINT!\n");
	signal(SIGINT,oldact);
}

int main(){
	
	oldact = signal(SIGINT,handler);

	while(1){
		sleep(1);
	}
}
