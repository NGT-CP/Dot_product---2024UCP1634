#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>

#define MAX 10000

char *format_text(char *s)
{
    static char out[MAX];
    int k = 0;

    for (int i = 0; s[i]; i++)
    {
        if (isspace(s[i]))
        {
            if (k > 0 && out[k - 1] != ' ')
                out[k++] = ' ';
        }
        else if (ispunct(s[i]))
        {
            while (k > 0 && out[k - 1] == ' ')
                k--;

            out[k++] = s[i];

            int j = i + 1;
            while (s[j] && isspace(s[j]))
                j++;

            if (s[j] && !ispunct(s[j]))
                out[k++] = ' ';
        }
        else
        {
            out[k++] = s[i];
        }
    }

    if (k > 0 && out[k - 1] == ' ')
        k--;

    out[k] = '\0';
    return out;
}

int main()
{
    int p1[2], p2[2], p3[2];

    pipe(p1);
    pipe(p2);
    pipe(p3);

    char filename[100];
    printf("Enter file name: ");
    scanf("%s", filename);

    FILE *fp = fopen(filename, "r");

    if (fp == NULL)
    {
        printf("File not found\n");
        return 1;
    }

    char text[MAX];
    int n = fread(text, 1, MAX - 1, fp);
    text[n] = '\0';
    fclose(fp);

    int pid2 = fork();

    if (pid2 == 0)
    {
        close(p1[1]);
        close(p2[0]);
        close(p3[0]);
        close(p3[1]);

        char input[MAX];
        read(p1[0], input, MAX);

        char *formatted = format_text(input);

        write(p2[1], formatted, strlen(formatted) + 1);

        close(p1[0]);
        close(p2[1]);

        exit(0);
    }

    int pid3 = fork();

    if (pid3 == 0)
    {
        close(p1[0]);
        close(p1[1]);
        close(p2[1]);
        close(p3[0]);

        char input[MAX];
        read(p2[0], input, MAX);

        int newword = 1;
        int count = 0;
        char output[MAX];
        int k = 0;

        for (int i = 0; input[i]; i++)
        {
            if (isalpha(input[i]))
            {
                if (newword)
                {
                    output[k++] = toupper(input[i]);
                    count++;
                    newword = 0;
                }
                else
                {
                    output[k++] = tolower(input[i]);
                }
            }
            else
            {
                output[k++] = input[i];

                if (isspace(input[i]) || ispunct(input[i]))
                    newword = 1;
            }
        }

        output[k] = '\0';

        printf("\nFinal formatted text:\n%s\n", output);
        printf("Word count = %d\n", count);

        write(p3[1], &count, sizeof(count));

        close(p2[0]);
        close(p3[1]);

        exit(0);
    }

    close(p1[0]);
    close(p2[0]);
    close(p2[1]);
    close(p3[1]);

    write(p1[1], text, strlen(text) + 1);
    close(p1[1]);

    int count;
    read(p3[0], &count, sizeof(count));

    printf("\nProcess 1: Total words = %d\n", count);

    wait(NULL);
    wait(NULL);

    close(p3[0]);

    return 0;
}
