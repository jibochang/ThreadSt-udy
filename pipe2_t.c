#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
	int pfd[2];
	int ret;
	int i;
	char buf[64];
	pid_t pid;
	ret = pipe(pfd);

	if(ret<0){
		perror("pipe");
		return 0;
	}
	for(i = 0;i < 2;i++){
		pid = fork();
		if(pid < 0){
			perror("fork");
		}else if(pid == 0){
			break;
		}else{
			
		}
	}
	if(i == 2){ //father
		close(pfd[1]);
		while(1){
			ret = read(pfd[0],buf,64);
			if(ret > 0){
				printf("%s\n",buf);
			}
		}
	}

	if(i == 1){ //son2
		close(pfd[0]);
		while(1){
			memset(buf,0,64);
			strcpy(buf,"This is second process!");
			write(pfd[1],buf,strlen(buf));
			sleep(1);
		}
	}

	if(i == 0){ //son1
		close(pfd[0]);
		while(1){
			memset(buf,0,64);
			strcpy(buf,"This is first process!");
			write(pfd[1],buf,strlen(buf));
			sleep(1);
		}
	}

	while(1){
		sleep(1);
	}


	return 0;
}
