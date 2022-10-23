#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void handle(int sig){
	printf("I got sig = %d\n",sig);
}

void mytask(){
	printf("My task start\n");
	sleep(2);
	printf("My task end\n");
}

int main(){

	struct sigaction act;
	act.sa_handler = handle;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGSEGV,&act,NULL);
	sigaction(SIGINT,&act,NULL);
	
	sigset_t set,set2;
	sigemptyset(&set2);
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGSEGV);

	pause();

	printf("After pause\n");
	while(1){
		sigprocmask(SIG_BLOCK,&set,NULL);
		mytask();
		//sigprocmask(SIG_UNBLOCK,&set,NULL);
		//pause();
		sigsuspend(&set2);
	}
}
