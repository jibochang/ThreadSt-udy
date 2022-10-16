#include <sys/mman.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){
	void* addr;
	addr = mmap(NULL,2048,PROT_READ|PROT_WRITE,MAP_SHARED|MAP_ANONYMOUS,-1,0);
	if(addr==MAP_FAILED){
		perror("mmap");
		return 0;
	}
	
	pid_t pid;
	pid = fork();
	if(pid<0){
		perror("fork");
		return 0;
	}else if(pid==0){
		usleep(10);
		printf("read:\n%s\n",(char*)addr);
	}else{
		memcpy(addr,"Hello,World!",12);
		wait(NULL);
	}

	munmap(addr,2048);
	//memcpy(addr+3000,"HelloWorld",10);
	//printf("read:\n%s\n",(char*)(addr+3000));
	return 0;
}
