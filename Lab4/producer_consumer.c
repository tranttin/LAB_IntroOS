#include<stdio.h>

#include<pthread.h>

#include<semaphore.h>

#include <unistd.h>

#include <stdlib.h>

#define BUFFER_SIZE 10

struct item {
    char s[100];
};

void * consume(void * arg);
void * produce(void * arg);
struct item buffer[BUFFER_SIZE];
int in = 0, out = 0;

int main(int argc, char * argv[]) {
    pthread_t tid1, tid2;

    int sleep1 = atoi(argv[1]);
    int sleep2 = atoi(argv[2]);
    pthread_create( & tid2, NULL, consume, (void * ) & sleep1);
    pthread_create( & tid1, NULL, produce, (void * ) & sleep2);

    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);
}

void * produce(void * arg) {
    printf("\nProducer start.");
    struct item message;
    while (1) {
        sleep( * ((int * ) arg));
        printf("\nProducer: ");
        fgets(message.s, 100, stdin);
        while ((( in +1) % BUFFER_SIZE) == out);
        buffer[ in ] = message; in = ( in +1) % BUFFER_SIZE;
        printf("\nPro in = %d and out = %d", in , out);

    }
    return NULL;
}
void * consume(void * arg) {
    struct item message;
    printf("\nConsumer start.");
    while (1) {
        printf("\nCon in = %d and out = %d", in , out);

        while ( in == out);
        message = buffer[out];

        printf("\n\t\tConsumer received: %s", message.s);
        out = (out + 1) % BUFFER_SIZE;
        sleep( * ((int * ) arg));
    }
    return NULL;
}
