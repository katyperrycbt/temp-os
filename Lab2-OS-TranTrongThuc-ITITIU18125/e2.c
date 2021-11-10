#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

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

int doTask(char *myNumber)
{
    if (!checkNumber(myNumber))
    {
        printf("%s is NOT a VALID number, on process %d \n", myNumber, (int)getpid());
    }
    else
    {
        int temp = atoi(myNumber);
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
            printf("%d is NOT a GROWING number, on process %d \n", atoi(myNumber), (int)getpid());
        }
        else if (arraySortedOrNot(arr, k))
        {
            printf("%d is a GROWING number, on process %d \n", atoi(myNumber), (int)getpid());
        }
        else
        {
            printf("%d is NOT a GROWING number, on process %d \n", atoi(myNumber), (int)getpid());
        }
    }
    return 1;
}

int main(int argc, char *argv[])
{
    int status = 0;

    for (int i = 1; i < argc; i++)
    {
        int pid = fork();
        if (pid == 0)
        {
            doTask(argv[i]);
            exit(0);
        }
        wait(&status);
    }
    return 0;
}