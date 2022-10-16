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
	ret = mkfifo("/home/ubuntu/myfifo",0666);
	if(ret<0){
		perror("mkfifo");
		//return 0;
	}
	fd = open("/home/ubuntu/myfifo",O_WRONLY);
	if(fd<0){
		perror("open");
		return 0;
	}

	while(1){
		fgets(buf,32,stdin);
		write(fd,buf,strlen(buf));
	}

	return 0;
}
