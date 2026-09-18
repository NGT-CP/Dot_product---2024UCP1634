#include <stdio.h>
#include <unistd.h>

int global = 10;

int main()
{
    int local = 20;
    static int stat = 30;

    int rc = fork();

    if(rc == 0)
    {
        printf("Child\n");
        printf("global = %p\n", &global);
        printf("local  = %p\n", &local);
        printf("static = %p\n", &stat);

        global++;
        local++;
        stat++;
    }
    else
    {
        printf("Parent\n");
        printf("global = %p\n", &global);
        printf("local  = %p\n", &local);
        printf("static = %p\n", &stat);
    }

    return 0;
}
