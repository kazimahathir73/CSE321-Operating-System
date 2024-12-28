#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    pid_t a, b;
    a = fork();
    if(a==0){
        b = fork();
        if(b>0){
            wait(NULL);
            printf("I am child\n");
        }
        else if(b==0){
            printf("I am grand child\n");
        }
    }
    else if(a>0){
        wait(NULL);
        printf("I am parent\n");
    }

    return 0;
}