#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/wait.h>

#define SIZE 5
#define ITEMS 5

typedef struct
{
    int buffer[SIZE];
    int in, out;

    int pflag[2], pturn;
    int cflag[2], cturn;

    int consumed;
} Shared;

void p_lock(Shared *s, int i)
{
    int j = 1 - i;

    s->pflag[i] = 1;
    s->pturn = j;

    while (s->pflag[j] && s->pturn == j)
        ;
}

void p_unlock(Shared *s, int i)
{
    s->pflag[i] = 0;
}

void c_lock(Shared *s, int i)
{
    int j = 1 - i;

    s->cflag[i] = 1;
    s->cturn = j;

    while (s->cflag[j] && s->cturn == j)
        ;
}

void c_unlock(Shared *s, int i)
{
    s->cflag[i] = 0;
}

int main()
{
    int choice;

    printf("1. SP-SC\n");
    printf("2. SP-MC\n");
    printf("3. MP-SC\n");
    printf("4. MP-MC\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int producers = 1;
    int consumers = 1;

    if (choice == 2)
        consumers = 2;

    if (choice == 3)
        producers = 2;

    if (choice == 4)
    {
        producers = 2;
        consumers = 2;
    }

    Shared *s = mmap(NULL, sizeof(Shared),
                     PROT_READ | PROT_WRITE,
                     MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    s->in = 0;
    s->out = 0;
    s->consumed = 0;

    s->pflag[0] = s->pflag[1] = 0;
    s->cflag[0] = s->cflag[1] = 0;

    int total = producers * ITEMS;

    for (int id = 0; id < producers; id++)
    {
        if (fork() == 0)
        {
            for (int x = 0; x < ITEMS; )
            {
                p_lock(s, id);

                int next = (s->in + 1) % SIZE;

                if (next != s->out)
                {
                    int value = id * 100 + x + 1;

                    s->buffer[s->in] = value;
                    s->in = next;

                    printf("P%d produced %d\n", id + 1, value);

                    x++;
                }

                p_unlock(s, id);

                usleep(100000);
            }

            return 0;
        }
    }

    for (int id = 0; id < consumers; id++)
    {
        if (fork() == 0)
        {
            while (1)
            {
                c_lock(s, id);

                if (s->consumed >= total)
                {
                    c_unlock(s, id);
                    break;
                }

                if (s->in != s->out)
                {
                    int value = s->buffer[s->out];
                    s->out = (s->out + 1) % SIZE;

                    s->consumed++;

                    printf("C%d consumed %d\n",
                           id + 1, value);
                }

                c_unlock(s, id);

                usleep(150000);
            }

            return 0;
        }
    }

    for (int i = 0; i < producers + consumers; i++)
        wait(NULL);

    munmap(s, sizeof(Shared));

    return 0;
}
