#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int count() {
    int f = open("count.txt", O_RDWR);
    char buff[10] = "";
    ssize_t bytes_read = read(f, buff, sizeof(buff) - 1);
    buff[bytes_read] = '\0';
    int num = atoi(buff);
    num++;
    snprintf(buff, sizeof(buff), "%d\n", num);
    lseek(f, 0, SEEK_SET);
    ssize_t bytes_written = write(f, buff, strlen(buff));
    close(f);
}

void pid_odd() {
    pid_t p = getpid();
    if (p % 2 != 0) {
        pid_t child_p = fork();
        if (child_p == 0) {
            count(); 
            exit(0);
        }
        wait(NULL);
        count();
    }
}

int main() {
    pid_t a, b, c;

    a = fork();
    if (a == 0) {
        pid_odd();
        exit(0);
    }
    else if(a>0){
        wait(NULL);
    }

    b = fork();
    if (b == 0) {
        pid_odd();
        exit(0);
    }
    else if(b>0){
        wait(NULL);
    }

    c = fork();
    if (c == 0) {
        pid_odd();
        exit(0);
    }
    else if(c>0){
        wait(NULL);
    }

    return 0;
}
