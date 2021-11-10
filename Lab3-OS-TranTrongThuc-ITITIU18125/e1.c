#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

struct myType
{
    long thread_id;
    char *num;
};

int arraySortedOrNot(int arr[], int n)
{
    if (n == 1 || n == 0)
        return 1;

    if (arr[n - 1] <= arr[n - 2])
        return 0;

    return arraySortedOrNot(arr, n - 1);
}

void rvereseArray(int arr[], int start, int end)
{
    int temp;
    while (start < end)
    {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

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

void *doTaskWithThread(void *myNumber)
{
    struct myType *args = myNumber;
    if (!checkNumber(args->num))
    {
        printf("%s is NOT a VALID number, \n", args->num);
    }
    else
    {
        int temp = atoi(args->num);
        int arr[100];
        int k = 0;
        while (temp > 0)
        {
            int digit = temp % 10;
            arr[k] = digit;
            k++;
            temp /= 10;
        }
        rvereseArray(arr, 0, k - 1);
        if (k == 1)
        {
            printf("%d is NOT a GROWING number, in thread %ld\n", atoi(args->num), args->thread_id);
        }
        else if (arraySortedOrNot(arr, k))
        {
            printf("%d is a GROWING number, in thread %ld\n", atoi(args->num), args->thread_id);
        }
        else
        {
            printf("%d is NOT a GROWING number, in thread %ld\n", atoi(args->num), args->thread_id);
        }
    }
}

int main(int argc, char *argv[])
{
    pthread_t threads[argc - 1];

    for (int i = 1; i < argc; i++)
    {
        struct myType plugh;
        plugh.thread_id = (long)&threads[i - 1];
        plugh.num = (char *)argv[i];

        pthread_create(&threads[i - 1], NULL, doTaskWithThread, (void *)&plugh);
        pthread_join(threads[i - 1], NULL);
    }

    return 0;
}