#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>

#define THREAD_NUM 4

sem_t semEmpty;
sem_t semFull;
pthread_mutex_t mutexBuffer;

//file pointer assignment statements.
FILE* input;
FILE* output;

int count = 0;

//A structure to store requests.
struct Request{
    int reqNo;
    int from;
    int to;
};

//A structure to store lift info.
struct Lift{
    int liftNo;
    int c_pos;
    int movement;
    int tMovement;
    int tRequests;
};

//Declaring and defining queue functions.
struct queue{
    int size;
    int f;
    int r;
    struct Request* arr;
};

int isEmpty(struct queue *q){
    if(q->r==q->f){
        return 1;
    }
    return 0;
};
 
int isFull(struct queue *q){
    if(q->r==q->size-1){
        return 1;
    }
    return 0;
};
 
void enqueue(struct queue *q, struct Request req){
    if(isFull(q)){
        printf("This Queue is full\n");
    }
    else{
        q->r++;
        q->arr[q->r] = req;
        printf("Enqued element.\n");
    }
};
 
struct Request dequeue(struct queue *q){
    struct Request r;
    if(isEmpty(q)){
        printf("This Queue is empty\n");
    }
    else{
        q->f++;
        r = q->arr[q->f]; 
    }
    return r;
};

//Declaring Buffer.
struct queue Buffer;

void* request(void* args) {

    struct Request r1;

    while (!feof(input)){
        sem_wait(&semEmpty);
        pthread_mutex_lock(&mutexBuffer);

        fscanf (input, "%d %d %d", &r1.reqNo, &r1.from, &r1.to);

        fprintf (output, "--------------------------------------------\n");
        fprintf (output, "Request No: %d\n", r1.reqNo);
        fprintf (output, "From Floor %d to Floor %d\n", r1.from, r1.to);
        fprintf (output, "--------------------------------------------\n");
        
        if(isFull(&Buffer) != 1){
            enqueue(&Buffer, r1);
            count++;
        }
            
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semFull);
    }
}

void* lift(void* args) {
    sem_wait(&semFull);
    pthread_mutex_lock(&mutexBuffer);
    struct Lift l1 = *(struct Lift*)args;
    struct Request r1;
    pthread_mutex_unlock(&mutexBuffer);
    sem_post(&semEmpty);

    while(count > 0){
        sem_wait(&semFull);
        pthread_mutex_lock(&mutexBuffer);
        
        if(isEmpty(&Buffer) == 0){
            r1 = dequeue(&Buffer);
            count--;

            l1.movement = 0;//Resetting movement.
            l1.tRequests++;//Incrementing total requests.

            fprintf(output, "Lift %d Operations\nPrevious Position: %d Floor\nRequest: number %d from Floor %d to Floor %d\n", l1.liftNo, l1.c_pos, r1.reqNo, r1.from, r1.to);
            fprintf(output, "Detail Operations:\n\tGo from Floor %d to Floor %d\n", l1.c_pos, r1.from);
            
            //Stimulating lift movement.
            sleep(1);
            l1.movement += abs(l1.c_pos - r1.from);
            l1.c_pos = r1.from;
            
            fprintf(output, "\tGo from Floor %d to Floor %d\n", r1.from, r1.to);
            
            sleep(1);
            l1.movement += abs(r1.to - r1.from);
            l1.c_pos = r1.to;

            //Adding to total movement.
            l1.tMovement += l1.movement;

            fprintf(output, "\t#movement for this request: %d\n", l1.movement);
            fprintf(output, "\t#Requests: %d\n", l1.tRequests);
            fprintf(output, "\tTotal #movement: %d\n", l1.tMovement);
            fprintf(output, "Current Position: %d Floor\n", r1.to);
        }
        
        pthread_mutex_unlock(&mutexBuffer);
        sem_post(&semEmpty);
    }
}

int main(int argc, char* argv[]) {
    //Creating thread array, mutexes, semaphores, and lifts.
    pthread_t threads[THREAD_NUM];
    pthread_mutex_init(&mutexBuffer, NULL);
    sem_init(&semEmpty, 0, 10);
    sem_init(&semFull, 0, 0);
    Buffer.size = 10;
    Buffer.f , Buffer.r = -1;
    Buffer.arr = malloc(sizeof(struct Request)*Buffer.size);
    struct Lift l1, l2, l3;
    
    //Setting values for lifts.
    l1.liftNo = 1;
    l2.liftNo = 2;
    l3.liftNo = 3;    
    l1.c_pos = 1; 
    l2.c_pos= 1; 
    l3.c_pos = 1;
    l1.tMovement = 0;
    l2.tMovement = 0;
    l3.tMovement = 0;
    l1.tRequests = 0;
    l2.tRequests = 0;
    l3.tRequests = 0;
    l1.movement = 0;
    l2.movement = 0;
    l3.movement = 0;

    //Dynamically allocating lifts for use in threads.
    struct Lift* lift1 = malloc(sizeof(struct Lift));
    *lift1 = l1;
    struct Lift* lift2 = malloc(sizeof(struct Lift));
    *lift2 = l3;
    struct Lift* lift3 = malloc(sizeof(struct Lift));
    *lift3 = l2;

    //assigning files to file pointers.
    input = fopen("sim_input.txt", "r");
    if(input == NULL){
        printf("No file read.\n\n");
        return -1;
    }
    else{
        fseek(input, 0, SEEK_SET);
        printf("File read successfully.\n\n");
    }
    output = fopen("sim_out.txt", "w");
    if(output == NULL){
        printf("No file read.\n\n");
        return -1;
    }
    else{
        printf("File read successfully.\n\n");
    }

    //Creating threads and passing lift structures.
    if (pthread_create(&threads[0], NULL, &request, NULL) != 0) {
        perror("Failed to create thread");
    }

    if (pthread_create(&threads[1], NULL, &lift, lift1) != 0) {
        perror("Failed to create thread");
    }
    if (pthread_create(&threads[2], NULL, &lift, lift2) != 0) {
        perror("Failed to create thread");
    }
    if (pthread_create(&threads[3], NULL, &lift, lift3) != 0) {
        perror("Failed to create thread");
    }

    //Joining all threads using loop structure.    
    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Failed to join thread");
        }
    }
    
    //Freeing memory.
    if(count < 1 && isEmpty(&Buffer) == 1){
        sem_destroy(&semEmpty);
        sem_destroy(&semFull);
        pthread_mutex_destroy(&mutexBuffer);
        fclose(input);
        fclose(output);
        free(lift1);    
        free(lift2);
        free(lift3);
    }
    return 0;
}