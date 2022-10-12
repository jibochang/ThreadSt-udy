#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>


pthread_cond_t  hasTaxi=PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock  = PTHREAD_MUTEX_INITIALIZER;


struct taxi{
    struct taxi *next;
    int num;

};

struct taxi *Head=NULL;

void *taxiarv(void *arg){
    printf("taxi arrived thread\n");
    pthread_detach(pthread_self());
    struct taxi *tx;
    int i=1;
    while(1){
        tx = malloc(sizeof(struct taxi));
        tx->num = i++;
        printf("taxi %d comming\n",tx->num);
        pthread_mutex_lock(&lock);
        tx->next = Head;
        Head = tx;
        pthread_cond_signal(&hasTaxi);
        //pthread_cond_broadcast(&hasTaxi);
        pthread_mutex_unlock(&lock);
        sleep(1);
    }
    pthread_exit(0);
}

void *takeTaxi(void *arg){
    printf("take taxi thread\n");
    pthread_detach(pthread_self());
    struct taxi *tx;
    while(1){
        pthread_mutex_lock(&lock);
        while(Head==NULL)
        {
            pthread_cond_wait(&hasTaxi,&lock);
        }
        tx = Head;
        Head=tx->next;
        printf("%d,Take taxi %d\n",(int)arg,tx->num);
        free(tx);
        pthread_mutex_unlock(&lock);
    }
    pthread_exit(0);
}

int main(){
    pthread_t tid1,tid2,tid3;

    pthread_create(&tid1,NULL,taxiarv,NULL);
//    sleep(5);
    pthread_create(&tid2,NULL,takeTaxi,(void*)1);
    pthread_create(&tid2,NULL,takeTaxi,(void*)2);
    pthread_create(&tid2,NULL,takeTaxi,(void*)3);

    while(1) {
        sleep(1);

    }


}

