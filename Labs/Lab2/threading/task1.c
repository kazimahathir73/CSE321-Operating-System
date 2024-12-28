#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void *thread_func(void *arg) {
    int t_num = *(int *)arg;
    printf("thread-%d running\n", t_num);
    sleep(1);
    printf("thread-%d closed\n", t_num);
    return NULL;
}

int main() {
    pthread_t thread[5];

    for (int i = 0; i <= 5; i++) {
        pthread_create(&thread[i-1], NULL, thread_func, &i);
        pthread_join(thread[i-1], NULL);
    }

    return 0;
}
