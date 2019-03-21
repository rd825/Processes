// Write a program that forks a child and creates a shared pipe
// between the parent and child processes. Have the child write
// the three messages to the parent and have the parent print out
// the messages.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <string.h>

#define MSGSIZE 16

char *msg1 = "hello world #1";
char *msg2 = "hello world #2";
char *msg3 = "hello world #3";

int main(void)
{
    // Your code here
    int myPipe[2];
    if (pipe(myPipe) == -1)
    {
        fprintf(stderr, "Pipe Failed");
        return 1;
    }

    int rc = fork();

    // ------------------------------------------------ child process starts executing here
    if (rc < 0)
    { // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    { // child process satisfies this branch
        printf("Child started\n");
        write(myPipe[1], msg1, strlen(msg1 + 1));
        write(myPipe[1], msg2, strlen(msg2 + 1));
        write(myPipe[1], msg3, strlen(msg3 + 1));
        close(myPipe[1]);
        printf("Child ended\n");
    }
    else
    {
        wait(NULL);
        printf("Parent started\n");
        read(myPipe[0], msg1, 100);
        read(myPipe[0], msg2, 100);
        read(myPipe[0], msg3, 100);

        printf("%s\n", msg1);
        printf("%s\n", msg2);
        printf("%s\n", msg3);

        close(myPipe[0]);
        printf("Parent ended\n");
    }

    return 0;
}
