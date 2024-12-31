#include <pthread.h>
#include <stdio.h>
#include <string.h>
#define MAX 10
#define BUFLEN 6
#define NUMTHREAD 2
void *consumer(void *id);
void *producer(void *id);

char buffer[BUFLEN];
char source[BUFLEN];
int pCount = 0;
int cCount = 0;
int buflen;

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t nonEmpty = PTHREAD_COND_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
int thread_id[NUMTHREAD] = {0, 1};
int i = 0;
int j = 0;

int main()
{
    int i;
    pthread_t thread[NUMTHREAD];

    strcpy(source, "abcdef");
    buflen = strlen(source);

    pthread_create(&thread[0], NULL, producer, &thread_id[0]);
    pthread_create(&thread[1], NULL, consumer, &thread_id[1]);

    for (int i = 0; i < 2; i++)
    {
        pthread_join(thread[i], NULL);
    }

    return 0;
}

void *producer(void *id)
{
    int *thread_id = id;
    while (i < MAX)
    {
        pthread_mutex_lock(&count_mutex);
        while ((pCount + 1) % BUFLEN == cCount)
        {
            pthread_cond_wait(&full, &count_mutex);
        }

        char next_produced = source[pCount];
        buffer[pCount] = next_produced;
        printf("%d produced %c by Thread %d\n", i, next_produced, *thread_id);
        pCount = (pCount + 1) % BUFLEN;
        buflen++;
        i++;
        pthread_cond_signal(&nonEmpty);
        pthread_mutex_unlock(&count_mutex);
    }
}

void *consumer(void *id)
{
    int *thread_id = id;
    while (j < MAX)
    {
        pthread_mutex_lock(&count_mutex);
        while (cCount == pCount)
        {
            pthread_cond_wait(&nonEmpty, &count_mutex);
        }
        char next_consumed = buffer[cCount];
        cCount = (cCount + 1) % BUFLEN;
        printf("%d consumed %c by Thread %d\n", j, next_consumed, *thread_id);
        buflen--;
        j++;
        pthread_cond_signal(&full);
        pthread_mutex_unlock(&count_mutex);
    }
}
