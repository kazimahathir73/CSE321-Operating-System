#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

#define MaxCrops 5
#define warehouseSize 5
sem_t empty;
sem_t full;
int in = 0;
int out = 0;
char crops[warehouseSize] = {'R', 'W', 'P', 'S', 'M'};
char warehouse[warehouseSize] = {'N', 'N', 'N', 'N', 'N'};
pthread_mutex_t mutex;

void *Farmer(void *far)
{
    int *farmer_id = far;

    for (int i = 0; i < MaxCrops; i++)
    {
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        char crop_harvested = crops[in];
        warehouse[in] = crop_harvested;
        printf("Farmer %d: Insert crops %c at %d\n", *farmer_id, warehouse[in], in);
        in = (in + 1) % warehouseSize;

        pthread_mutex_unlock(&mutex);
        sem_post(&full);
    }
    printf("Farmer %d: %s\n", *farmer_id, warehouse);
}
void *ShopOwner(void *sho)
{
    int *shop_owner_id = sho;

    for (int i = 0; i < MaxCrops; i++)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);

        char crop_taken = warehouse[out];
        warehouse[out] = 'N';
        printf("Shop owner %d: Remove crops %c from %d\n", *shop_owner_id, crop_taken, out);
        out = (out + 1) % warehouseSize;

        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
    }
    printf("Shop owner %d: %s\n", *shop_owner_id, warehouse);
}
int main()
{
    pthread_t Far[5], Sho[5];
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, warehouseSize);
    sem_init(&full, 0, 0);
    int a[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++)
    {
        pthread_create(&Far[i], NULL, Farmer, &a[i]);
        pthread_create(&Sho[i], NULL, ShopOwner, &a[i]);
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(Far[i], NULL);
        pthread_join(Sho[i], NULL);
    }

    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}