#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_mutex_t mutex;
sem_t write_sem;
int read_count=0;
int shared_data=0;

void *reader(void *arg) {
    int id = *((int *)arg);

    pthread_mutex_lock(&mutex);
    read_count++;

    if(read_count == 1) {
        sem_wait(&write_sem);
    }
    pthread_mutex_unlock(&mutex);

    print("Reader %d: Read data = %d\n", id, shared_data);
    sleep(1)

    pthread_mutex_lock(&mutex);
    read_count--;
    if(read_count==0) sem_post(&write_sem);
    pthread_mutex_unlock(&mutex);
    return NULL;
}

void *writer(void *arg){
    int id = *((int *)arg);

    sem_wait(&write_sem);
    shared_data++;
    print("Write %d: Wrote data = %d\n", id, shared_data);
    sleep(1);

    sem_post(&write_sem);

    return NULL;
}

int main() {
    pthread_t r[5], w[2];
    int reader_ids[5] = {1, 2, 3, 4, 5};
    int writer_ids[2] = {1, 2};

    pthread_mutex_init(&mutex, NULL);
    sem_init(&write_sem, 0, 1);

    for(int i=0; i<2; i++){
        pthread_create(&w[i], NULL, writer, &writer_ids[i]);
    }

    for(int i=0; i<5; i++){
        pthread_create(&r[i], NULL, reader, &reader_ids[i]);
    }

    for(int i=0; i<2; i++){
        pthread_join(w[i], NULL);
    }

    for(int i=0; i<5; i++){
        pthread_join(r[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&write_sem);

    return 0;
}