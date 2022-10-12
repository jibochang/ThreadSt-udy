#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
	int pfd[2];
	int ret;
	char buf[20];
	pid_t pid;
	ret = pipe(pfd);

	if(ret<0){
		perror("pipe");
		return 0;
	}

	pid = fork();

	if(pid < 0){
		perror("fork");
		return 0;
	}else if(pid == 0){
		while(1){
			strcpy(buf,"HelloWorld!");
			write(pfd[1],buf,strlen(buf));
			sleep(1);
		}
	}else{
		while(1){
			ret = read(pfd[0],buf,20);
			if(ret>0){
				printf("read pipe = %s\n",buf);
			}
		}
	}

	return 0;
}
