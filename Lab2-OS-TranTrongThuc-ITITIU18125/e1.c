#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#define MAX_SIZE 100

bool checkNumber(char *n)
{
    for (int i = 0; i < strlen(n); i++)
    {
        if (n[i] < '0' || n[i] > '9')
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++)
    {
        if (!checkNumber(argv[i]))
        {
            printf("Array contain INVALID number %s \n", argv[i]);
            return 0;
        }
    }
    int i, max, min, size;

    size = argc;

    int rc = fork();

    if (rc < 0)
    {
    }
    else if (rc == 0)
    {
        max = atoi(argv[1]);
        for (i = 1; i < size; i++)
        {
            if (atoi(argv[i]) > max)
            {
                max = atoi(argv[i]);
            }
        }
        printf("Process (pid:%d) Max: %d\n", (int)getpid(), max);
    }
    else
    {
        min = atoi(argv[1]);
        for (i = 1; i < size; i++)
        {
            if (atoi(argv[i]) < min)
            {
                min = atoi(argv[i]);
            }
        }
        printf("Process (pid:%d) Min: %d\n", (int)getpid(), min);
    }

    return 0;
}