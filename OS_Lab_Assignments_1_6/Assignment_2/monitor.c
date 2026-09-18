#include <stdio.h>
#include <unistd.h>

void cpu()
{
    FILE *f = fopen("/proc/loadavg", "r");

    char x[100];
    fgets(x, 100, f);

    printf("Load: %s", x);

    fclose(f);
}

void memory()
{
    FILE *f = fopen("/proc/meminfo", "r");

    char x[100];

    for(int i = 0; i < 3; i++)
    {
        fgets(x, 100, f);
        printf("%s", x);
    }

    fclose(f);
}

int main()
{
    for(int i = 0; i < 5; i++)
    {
        printf("\n--- Monitor ---\n");

        cpu();
        memory();

        sleep(2);
    }

    return 0;
}
