#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <semaphore.h>

typedef struct
{
    int VAR;
    sem_t sem;
} Shared;

int main()
{
    Shared *s = mmap(NULL, sizeof(Shared),
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    s->VAR = 10;

    sem_init(&s->sem, 1, 0);

    if (fork() == 0)
    {
        s->VAR -= 2;

        printf("Child: VAR = %d\n", s->VAR);

        sem_post(&s->sem);

        return 0;
    }
    else
    {
        sem_wait(&s->sem);

        s->VAR += 2;

        printf("Parent: VAR = %d\n", s->VAR);

        wait(NULL);
    }

    sem_destroy(&s->sem);
    munmap(s, sizeof(Shared));

    return 0;
}
