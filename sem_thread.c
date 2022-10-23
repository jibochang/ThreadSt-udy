#include <fcntl.h>
#include <sys/stat.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <signal.h>
#include <pthread.h>

sem_t sem_r,sem_w;
char* shmaddr;

void *readmem(void *arg){
	while(1){
		sem_wait(&sem_r);
		printf("%s\n",shmaddr);
		sem_post(&sem_w);
	}
}


void delsemfile(int sig){
//	sem_unlink("mysem_r");
	sem_destroy(&sem_r);
	sem_destroy(&sem_w);
	exit(0);
}

int main(){
	struct sigaction act;
	act.sa_handler = delsemfile;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(SIGINT,&act,NULL);
	
	//sem_t *sem_r,*sem_w;
	key_t key;
	int shmid;
	//char* shmaddr;
	key = ftok(".",100);
	if(key<0){
		perror("ftok");
		return 0;
	}

	shmid = shmget(key,500,0666|IPC_CREAT);
	if(shmid<0){
		perror("shmget");
		return 0;
	}

	shmaddr = shmat(shmid,NULL,0);
	
	//sem_r = sem_open("mysem_r",O_CREAT|O_RDWR,0666,0);
	//sem_w = sem_open("mysem_w",O_CREAT|O_RDWR,0666,1);
	
	sem_init(&sem_r,0,0);
	sem_init(&sem_w,0,1);

	pthread_t tid;
	pthread_create(&tid,NULL,readmem,0);

	while(1){
		sem_wait(&sem_w);
		printf(">");
		fgets(shmaddr,500,stdin);
		//printf("%s\n",shmaddr);
		sem_post(&sem_r);
	}
}
