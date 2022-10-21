#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void handler(int sig){
	wait(NULL);
	printf("Get sig = %d\n",sig);
}

int main(){
	pid_t pid;
	struct sigaction act;
	act.sa_handler = handler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	//pid = fork();

	while(1){
		pid = fork();
		if(pid>0){
			sigaction(SIGCHLD,&act,NULL);
			//while(1){
				printf("Father process's waiting!\n");
				sleep(1);
			//}
			//wait(NULL);
		}else if(pid == 0){
			sleep(5);
			exit(0);

		
		}
	}

}
