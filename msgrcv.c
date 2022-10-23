#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>

typedef struct{
	long msg_type;
	char buf[128];
}msgT;

#define MSGLEN (sizeof(msgT)-sizeof(long))

int main(){
	key_t key;
	int msgid;
	int ret;
	msgT msg;

	key = ftok(".",100);
	if(key<0){
		perror("ftok");
		return 0;
	}
	msgid = msgget(key,IPC_CREAT|0666);
	if(msgid<0){
		perror("msgget");
		//return 0;
	}

	//msg.msg_type = 1;
	//strcpy(msg.buf,"This is msg_type=1\n");
	while(1){
		ret = msgrcv(msgid,&msg,MSGLEN,0,0);
		if(ret<0){
			perror("msgrcv");
			return 0;
		}

		printf("Rcv: msgtype:%ld\nbuf:%s\n",msg.msg_type,msg.buf);
	
	}
}
