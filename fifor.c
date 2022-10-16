#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int ret;
	int fd;
	char buf[32];
	/*
	ret = mkfifo("/home/ubuntu/myfifo",0666);
	if(ret<0){
		perror("mkfifo");
		return 0;
	}
	*/
	fd = open("/home/ubuntu/myfifo",O_RDONLY);
	if(fd<0){
		perror("open");
		return 0;
	}

	while(1){
		ret = read(fd,buf,32);
		if(ret>0){
			printf("read fifo = %s\n",buf);
		}else if(ret==0){
			exit(0);
		}
	}

	return 0;
}
