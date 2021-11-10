#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool isPerfectSquare(int x)
{
    int s = sqrt(x);
    return (s * s == x);
}

bool isFibonacci(int n)
{

    return isPerfectSquare(5 * n * n + 4) ||
           isPerfectSquare(5 * n * n - 4);
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
    for (int i = 1; i < argc; i++)
    {
        if (!checkNumber(argv[i]))
        {
            printf("%s is NOT a VALID number \n", argv[i]);
        }
        else
        {
            int temp = atoi(argv[i]);
            if (isFibonacci(temp))
            {
                printf("%d is a Fibonacci number \n", temp);
            }
            else
            {
                printf("%d is NOT a Fibonacci number \n", temp);
            }
        }
    }
    return 0;
}