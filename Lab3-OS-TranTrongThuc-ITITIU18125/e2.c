#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <time.h>

int sizeArray = 0;
long thread_id1 = 0;
long thread_id2 = 0;

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int arr[], int n, bool asc)
{
    int i, j, min_idx;

    if (asc)
    {
        for (i = 0; i < n - 1; i++)
        {
            min_idx = i;
            for (j = i + 1; j < n; j++)
                if (arr[j] < arr[min_idx])
                    min_idx = j;
            swap(&arr[min_idx], &arr[i]);
        }
    }
    else
    {
        for (i = 0; i < n - 1; i++)
        {
            min_idx = i;
            for (j = i + 1; j < n; j++)
                if (arr[j] > arr[min_idx])
                    min_idx = j;
            swap(&arr[min_idx], &arr[i]);
        }
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void *ascending(void *args)
{
    int *arr = (int *)args;
    int n = sizeArray;
    printf("Increasing order by thread %ld: ", thread_id1);
    selectionSort(arr, n, true);
    printArray(arr, n);
}

void *descending(void *args)
{
    int *arr = (int *)args;
    int n = sizeArray;
    printf("Decreasing order by thread %ld: ", thread_id2);
    selectionSort(arr, n, false);
    printArray(arr, n);
}

void printRandomsAndSortThem(int count)
{
    sizeArray = count;
    int rs[count + 1];
    printf("Generated: ");
    for (int i = 0; i < count; i++)
    {
        int num = (rand() % (100 - 1 + 1)) + 1;
        rs[i] = num;
        printf("%d ", num);
    }
    printf("\n");

    pthread_t asc, desc;
    asc = pthread_self();
    desc = pthread_self();
    thread_id1 = (long)asc;
    thread_id2 = (long)desc;

    pthread_create(&asc, NULL, ascending, rs);
    pthread_create(&desc, NULL, descending, rs);

    pthread_join(asc, NULL);
    pthread_join(desc, NULL);
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

int main(int argc, char *argv[])
{
    if (!checkNumber(argv[1]) || atoi(argv[1]) < 2 || atoi(argv[1]) > 11)
    {
        printf("???????????????????\n'%s' is not a VALID number (2<n<11), this argument has been skipped\n???????????????????\n", argv[1]);
    }
    else
    {
        int numberOfRandomNumber = atoi(argv[1]);
        printRandomsAndSortThem(numberOfRandomNumber);
    }

    return 0;
}
