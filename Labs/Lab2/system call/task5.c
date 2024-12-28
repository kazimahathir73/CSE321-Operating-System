#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    pid_t a,b;
    a = fork();
    if(a>0){
        printf("1. Parent process ID: %d\n",getpid());
        wait(NULL);
    }
    else if(a==0){
        printf("2. Child process ID: %d\n",getpid());
        for(int i=0; i<3; i++){
            b = fork();
            if (b == 0) {
                printf("%d. Grand Child process ID: %d\n", i+3, getpid());
                exit(EXIT_SUCCESS);
            }
        }
    }

    return 0;
}