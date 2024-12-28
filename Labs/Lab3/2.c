#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>

struct msg
{
    long int type;
    char txt[6];
};

int main()
{
    char workspace[6];
    printf("Please enter the workspace name:\n");
    scanf("%s", workspace);
    if (strcmp(workspace, "cse321") != 0)
    {
        printf("Invalid workspace name\n");
    }
    else
    {
        struct msg data;
        pid_t generator = fork();
        int msgid = msgget((key_t)12, IPC_CREAT | 0666);

        if (generator > 0)
        {
            data.type = 5;
            strcpy(data.txt, workspace);

            int msg_sent = msgsnd(msgid, (void *)&data, sizeof(data.txt), 0);
            printf("Workspace name sent to otp generator from log in: %s\n\n", data.txt);
            wait(NULL);
            int otp_received = msgrcv(msgid, (void *)&data, sizeof(data.txt), 0, IPC_NOWAIT);
            printf("Log in received OTP from OTP generator: %s\n", data.txt);
            struct msg data2;
            int mail_received = msgrcv(msgid, (void *)&data2, sizeof(data2.txt), 0, IPC_NOWAIT);
            printf("Log in received OTP from mail: %s\n", data2.txt);
            if (strcmp(data.txt, data2.txt) == 0)
            {
                printf("OTP Verified\n");
            }
            else
            {
                printf("OTP Incorrect\n");
            }
            msgctl(msgid, IPC_RMID, NULL);
        }

        else if (generator == 0)
        {
            struct msg r_data;
            int received = msgrcv(msgid, (void *)&r_data, sizeof(r_data.txt), 5, IPC_NOWAIT);
            printf("OTP generator received workspace name from log in: %s\n\n", r_data.txt);

            sprintf(r_data.txt, "%d", getpid());
            r_data.type = 6;
            int otp_sent = msgsnd(msgid, (void *)&r_data, sizeof(r_data.txt), 0);
            printf("OTP sent to log in from OTP generator: %s\n", r_data.txt);

            r_data.type = 7;
            int mail_sent = msgsnd(msgid, (void *)&r_data, sizeof(r_data.txt), 0);
            printf("OTP sent to mail from OTP generator: %s\n", r_data.txt);
            pid_t mail = fork();
            wait(NULL);
            if (mail == 0)
            {
                struct msg mail_data;
                int mail_received = msgrcv(msgid, (void *)&mail_data, sizeof(mail_data.txt), 7, IPC_NOWAIT);
                printf("Mail received OTP from OTP generator: %s\n", mail_data.txt);
                mail_data.type = 8;
                int otp_from_mail = msgsnd(msgid, (void *)&mail_data, sizeof(mail_data.txt), 0);
                printf("OTP sent to log in from mail: %s\n", mail_data.txt);
            }
        }
    }
    return 0;
}