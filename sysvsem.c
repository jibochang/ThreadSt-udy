#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/sem.h>


#define SEM_READ 0
#define SEM_WRITE 1

union semun{
	int val;
};

void P_operation(int semid,int semindex){
	struct sembuf sbuf;
	sbuf.sem_num = semindex;
	sbuf.sem_op = -1;
	sbuf.sem_flg = 0;

	semop(semid,&sbuf,1);
	
}

void V_operation(int semid,int semindex){
	struct sembuf sbuf;
        sbuf.sem_num = semindex;
        sbuf.sem_op = 1;
        sbuf.sem_flg = 0;

        semop(semid,&sbuf,1);
}

int main(){
	key_t key;
	int semid,shmid;
	char *shmaddr;
	key = ftok(".",100);
	if(key<0){
		perror("ftok");
		return 0;
	}

	semid = semget(key,2,IPC_CREAT|0666);
	if(semid<0){
		perror("semget");
		return 0;
	}

	shmid = shmget(key,500,IPC_CREAT|0666);
	shmaddr = shmat(shmid,NULL,0);
	
	union semun mysem;
	mysem.val = 0;
	semctl(semid,SEM_READ,SETVAL,mysem);
	mysem.val = 1;
	semctl(semid,SEM_WRITE,SETVAL,mysem);

	pid_t pid;
	pid = fork();
	if(pid<0){
		perror("fork");
		shmctl(shmid,IPC_RMID,NULL);
		semctl(semid,0,IPC_RMID);
		exit(-1);
	}else if(pid == 0){
		while(1){
			P_operation(semid,SEM_READ);	
			printf("%s\n",shmaddr);
			V_operation(semid,SEM_WRITE);
		}
	}else{
		while(1){
			P_operation(semid,SEM_WRITE);
			printf(">");
			fgets(shmaddr,32,stdin);
			V_operation(semid,SEM_READ);
		
		}
	}
}
