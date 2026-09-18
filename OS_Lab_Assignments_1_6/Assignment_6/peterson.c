#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SIZE 5
#define ITEMS 10

typedef struct
{
    int flag[2];
    int turn;

    int buffer[SIZE];
    int in, out, count;
} Shared;

void lock(Shared *s, int i)
{
    int j = 1 - i;

    s->flag[i] = 1;
    s->turn = j;

    while (s->flag[j] && s->turn == j)
        ;
}

void unlock(Shared *s, int i)
{
    s->flag[i] = 0;
}

int main()
{
    Shared *s = mmap(NULL, sizeof(Shared),
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    s->flag[0] = s->flag[1] = 0;
    s->turn = 0;
    s->in = s->out = s->count = 0;

    if (fork() == 0)
    {
        for (int x = 1; x <= ITEMS; x++)
        {
            while (1)
            {
                lock(s, 0);

                if (s->count < SIZE)
                {
                    s->buffer[s->in] = x;
                    s->in = (s->in + 1) % SIZE;
                    s->count++;

                    printf("Produced %d\n", x);

                    unlock(s, 0);
                    break;
                }

                unlock(s, 0);
            }

            usleep(100000);
        }

        return 0;
    }

    if (fork() == 0)
    {
        int done = 0;

        while (done < ITEMS)
        {
            lock(s, 1);

            if (s->count > 0)
            {
                int x = s->buffer[s->out];

                s->out = (s->out + 1) % SIZE;
                s->count--;

                printf("Consumed %d\n", x);

                done++;
            }

            unlock(s, 1);

            usleep(150000);
        }

        return 0;
    }

    wait(NULL);
    wait(NULL);

    munmap(s, sizeof(Shared));

    return 0;
}
