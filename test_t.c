#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
	pid_t pid;
	pid = fork();
	if(pid < 0){
		perror("Fork");
	}else if(pid > 0){
		int i = 0;
		while(1){
			sleep(1);
			printf("Father proc %d",i);
			i++;
		}
	}else{
		int i = 0;
		while(1){
			sleep(1);
			printf("Son proc %d",i);
			i++;
		}
	}
	return 0;
}
