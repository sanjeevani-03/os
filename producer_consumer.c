#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int in=0, out=0;

sem_t empty, full;
pthread_mutex_t mutex;

void *producer(void *arg){
    int id =  *((int *) arg);

    for(int i=0; i<5; i++){
        int item = (id*10)+i;

        sem_wait(&producer);
        pthread_mutex_lock(&mutex);

        buffer[in] = item;
        printf("Producer %d: produced item %d at position %d\n", id, item, in);
        in = (in+1)%BUFFER_SIZE;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);

        sleep(1);

    }

    return NULL;
}

voif consumer(coid *arg){
    int id = *((int *) arg);

    for(int i=0; i<5; i++){
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        int item = buffer[out];
        print("Consumer %d: consumed item %d from position %d", id, item, out);
        out=(out+1)%BUFFER_SIZE;
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }

    return NULL;
}

void main() {
    pthread_t pod[2], cons[2];
    int producer_ids[2] = {1, 2};
    int consumer_ids[2] = {1, 2};

    for(int i=0; i<2; i++){
        pthread_create(&prod[i], NULL, producer, &producer_ids[i]);
        pthread_create(&cons[i], NULL, consumer, &consumer_ids[i]);
    }

    for(int i=0; i<2; i++){
        pthred_join(prod[i], NULL);
        pthread_join(cons[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}