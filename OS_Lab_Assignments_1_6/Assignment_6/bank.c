#include <stdio.h>
#include <pthread.h>

int account[3] = {1000, 1000, 1000};

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *deposit(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&lock);

        for (int j = 0; j < 3; j++)
            account[j] += 100;

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

void *withdraw(void *arg)
{
    for (int i = 0; i < 5; i++)
    {
        pthread_mutex_lock(&lock);

        for (int j = 0; j < 3; j++)
        {
            if (account[j] >= 50)
                account[j] -= 50;
        }

        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main()
{
    pthread_t t1, t2;

    pthread_create(&t1, NULL, deposit, NULL);
    pthread_create(&t2, NULL, withdraw, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    for (int i = 0; i < 3; i++)
        printf("Account %d = %d\n", i + 1, account[i]);

    return 0;
}
