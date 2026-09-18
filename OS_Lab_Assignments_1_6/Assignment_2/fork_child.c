#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int rc = fork();

    if(rc == 0)
    {
        printf("Child process\n");
        printf("PID = %d\n", getpid());
    }
    else
    {
        wait(NULL);
        printf("Parent process\n");
    }

    return 0;
}
