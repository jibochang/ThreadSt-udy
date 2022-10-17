#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

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
	
	shmid = shmget(key,512,IPC_CREAT|0666);

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
	sleep(1);
	//strcpy(buf,"HelloWorld");
	printf("read:\n%s\n",buf);

	shmdt(buf);
	shmctl(shmid,IPC_RMID,NULL);
	//printf("read:\n%s\n",buf);
	return 0;
}
