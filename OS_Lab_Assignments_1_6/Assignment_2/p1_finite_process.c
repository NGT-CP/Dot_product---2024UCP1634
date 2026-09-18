#include <stdio.h>
#include <unistd.h>

int main()
{
    int n;

    printf("Enter n: ");
    scanf("%d", &n);

    for(int i = 0; i < n; i++)
    {
        printf("Process running %d\n", i + 1);
        sleep(1);
    }

    return 0;
}
