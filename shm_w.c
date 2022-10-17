#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>

int main(){
	key_t key;
	int shmid;
	char* buf;
	key = ftok("key_test",100);
	if(key<0){
		perror("ftok");
		return 0;
	}	
	printf("key=%x\n",key);
	
	shmid = shmget(key,512,0666);

	if(shmid<0){
		perror("shmget");
		return 0;
	}

	printf("shmid=%x\n",shmid);
	
	buf = shmat(shmid,NULL,0);
	if(buf<0){
		perror("shmat");
		return 0;	
	}

	strcpy(buf,"HelloWorld");
	return 0;
}
