#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    printf("Parent starting\n");

    int rc = fork();

    if(rc == 0)
    {
        printf("Child PID = %d\n", getpid());

        char *args[] = {
            (char *)"ls",
            (char *)"-l",
            NULL
        };

        execv("/bin/ls", args);

        exit(1);
    }
    else
    {
        wait(NULL);

        printf("Child finished\n");
        printf("Parent finished\n");
    }

    return 0;
}
