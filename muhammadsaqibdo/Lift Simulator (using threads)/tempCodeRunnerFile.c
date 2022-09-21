#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <conio.h>

struct Lift{
    int c_pos;
    int dest;
};

struct Request{
    int reqNo;
    int from;
    int to;
};

void request(){
    struct Request r1;
    r1.reqNo = 0;

    printf("before: %d\n", r1.reqNo);
    
    FILE* file;
    file = fopen("sim_input.txt", "r");
    if(file == NULL){
        printf("No file read.\n\n");
        return;
    }
    else{
        fseek(file, 0, SEEK_SET);
        printf("File read successfully.\n\n");
    }

    r1.reqNo = getw(file);
    printf("after: %d", r1.reqNo);
    fclose(file);

}

void* lift(){
    struct Lift l1;
    struct Request r1;

    sleep(3);
    l1.c_pos = r1.from;
    sleep(3);
    l1.c_pos = r1.to;

};

int main(){
    /*
    pthread_t Lift-1, Lift-2, Lift-3;
    pthread_create(&t1, NULL, &helloJee, NULL);
    pthread_create(&t2, NULL, &helloJee, NULL);
    pthread_create(&t3, NULL, &helloJee, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    */

    //helloJee();
    //printf("Hello, Mr.Mukadam :)\n");
    request();
    getch(); 
    return 0;
}