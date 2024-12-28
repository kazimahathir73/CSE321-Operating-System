#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <ctype.h>

struct shared {
    char sel[100];
    int b;
};

int main() {
    int fd[2];
    pid_t opr;
    char selected[100];
    pipe(fd);

    printf("Provide Your Input from Given Options\n");
    printf("1. Type a to Add Money\n2. Type w to Withdraw Money\n3. Type c to Check Balance\n");
    scanf("%s", selected);
    printf("Your Selection: %s\n", selected);

    int shmid = shmget((key_t)104, sizeof(struct shared), 0666 | IPC_CREAT);
    struct shared *shared1 = (struct shared *)shmat(shmid, NULL, 0);

    strcpy(shared1->sel, selected);
    shared1->b = 1000;

    opr = fork();

    if (opr > 0) {                          // Parent
        close(fd[1]);
        wait(NULL);

        char buff[200];
        read(fd[0], buff, sizeof(buff));
        close(fd[0]);

        printf("%s\n", buff);

        shmdt(shared1);
        shmctl(shmid, IPC_RMID, NULL);
    } else if (opr == 0) {                  // Child
        close(fd[0]);

        if (strlen(shared1->sel) == 1) {
            char action = shared1->sel[0];

            if (action == 'a') {
                int amount;
                printf("Enter amount to be added:\n");
                scanf("%d", &amount);

                if (amount > 0) {
                    shared1->b += amount;
                    printf("Balance added successfully\n");
                    printf("Updated balance after addition:\n%d\n", shared1->b);
                } else {
                    printf("Adding failed, Invalid amount\n");
                }
            } else if (action == 'w') {
                int amount;
                printf("Enter amount to be withdrawn:\n");
                scanf("%d", &amount);

                if (amount > 0 && amount <= shared1->b) {
                    shared1->b -= amount;
                    printf("Balance withdrawn successfully\n");
                    printf("Updated balance after withdrawal:\n%d\n", shared1->b);
                } else {
                    printf("Withdrawal failed, Invalid amount\n");
                }
            } else if (action == 'c') {
                printf("Your current balance is:\n%d\n", shared1->b);
            } else {
                printf("Invalid selection\n");
            }
        } else {
            printf("Invalid selection\n");
        }

        char data[] = "Thank you for using";
        write(fd[1], data, sizeof(data));
        close(fd[1]);
        exit(0);
    }

    return 0;
}