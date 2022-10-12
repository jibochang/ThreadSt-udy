#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		perror("fork");
	}else if(pid > 0){
		exit(0);
	}else{
		printf("I am son!\n");
	}
	printf("I am deamon!\n");
	printf("sid=%d,pid=%d,pgid=%d\n",getsid(getpid()),getpid(),getpgid(getpid()));
	if(setsid()<0){
		perror("sid");
		exit(0);
	}
	printf("After:\n");
	printf("sid=%d,pid=%d,pgid=%d",getsid(getpid()),getpid(),getpgid(getpid()));

	chdir("/");

	if(umask(0)<0){
		perror("umask");
		exit(-1);
	}

	for(int i = 0;i < 3;i++)
		close(i);

	printf("After close\n");

	sleep(100);
	return 0;
}
