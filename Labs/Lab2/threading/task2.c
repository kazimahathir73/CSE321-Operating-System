#include <stdio.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int count = 1;
void *thread_func(int *i){
	for (int j=0; j<5; j++){
		printf("Thread %d prints %d\n", *i, count);
		count++;
	}
}

int main() {
    pthread_t thread[5];
    for (int i = 0; i<5; i++) {
        pthread_create(&thread[i], NULL, thread_func, &i);
       	pthread_join(thread[i], NULL);
    }
    return 0;
}