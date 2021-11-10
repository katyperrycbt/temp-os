#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define P1_READ 0
#define P2_WRITE 1
#define P2_READ 2
#define P1_WRITE 3

#define P3_READ 4
#define P4_WRITE 5
#define P4_READ 6
#define P3_WRITE 7

#define NUM_PIPES 4

/**
 * Em chịu thầy ơi e hông kịp suy nghĩ bài 3 với syntax pipe e nắm ko rõ lắm :"", thầy có thể cho em xin đáp án với nha thầy
 * */

int main(int argc, char *argv[])
{
    int i, size, sumodd, sumeven;
    int pid1 = fork();
    int pid2 = fork();
    int fd[2 * NUM_PIPES];
    int val = 0, len;

    for (i = 0; i < NUM_PIPES; ++i)
    {
        if (pipe(fd + (i * 2)) < 0)
        {
            perror("Failed to allocate pipes");
            exit(EXIT_FAILURE);
        }
    }

    size = argc;

    int odds[50];
    int oddI = 0;
    int evens[50];
    int evenI = 0;

    if (pid1 != 0)
    {
        waitpid(pid1, NULL, 0);
    }
    if (pid2 != 0)
    {
        waitpid(pid2, NULL, 0);
    }

    for (int i = 1; i < size; i++)
    {
        if (atoi(argv[i]) % 2 == 0)
        {
            evens[evenI++] = atoi(argv[i]);
        }
        else
        {
            odds[oddI++] = atoi(argv[i]);
        }
    }

    if (pid1 == 0 && pid2 > 0)
    {
        close(fd[P1_READ]);
        close(fd[P1_WRITE]);
        close(fd[P3_READ]);
        close(fd[P3_WRITE]);
        len = read(fd[P2_READ], &evens, sizeof(evens));

        if (len > 0)
        {
            int sumeven = 0;
            for (int i = 0; i < evenI - 1; i++)
            {
            sumeven = sumeven + evens[i];
            }
            printf("The sum of even numbers is %d on process %d \n", sumeven, getpid());
            write(fd[P2_WRITE], &sumeven, sizeof(sumeven)) < 0;
        }

        close(fd[P2_READ]);
        close(fd[P2_WRITE]);
        close(fd[P4_READ]);
        close(fd[P4_WRITE]);

        return EXIT_SUCCESS;
    }
    else if (pid1 > 0 && pid2 == 0)
    {
        close(fd[P1_READ]);
        close(fd[P1_WRITE]);
        close(fd[P3_READ]);
        close(fd[P3_WRITE]);
        len = read(fd[P4_READ], &odds, sizeof(odds));

        if (len > 0)
        {
            int sumodd = 0;
            for (int i = 0; i < oddI - 1; i++)
            {
            sumodd = sumodd + odds[i];
            }
            printf("The sum of odd numbers is %d on process %d \n", sumodd, getpid());
            write(fd[P4_WRITE], &sumodd, sizeof(sumodd)) < 0;
        }

        close(fd[P2_READ]);
        close(fd[P2_WRITE]);
        close(fd[P4_READ]);
        close(fd[P4_WRITE]);

        return EXIT_SUCCESS;
    }
    else if (pid1 > 0 && pid2 > 0)
    {
        close(fd[P2_READ]);
        close(fd[P2_WRITE]);
        close(fd[P4_READ]);
        close(fd[P4_WRITE]);

        write(fd[P1_WRITE], &evens, sizeof(evens)) != sizeof(evens);
        write(fd[P3_WRITE], &odds, sizeof(odds)) != sizeof(odds);
        len = read(fd[P1_READ], &sumodd, sizeof(sumodd));
        len = read(fd[P3_READ], &sumeven, sizeof(sumeven));

        if (len > 0)
        {
            printf("The sum of odd numbers is %d and the sum of even numbers is %d on process %d \n", sumodd, sumeven, getpid());
        }

        close(fd[P1_READ]);
        close(fd[P1_WRITE]);
        close(fd[P3_READ]);
        close(fd[P3_WRITE]);

        wait(NULL);
        return EXIT_SUCCESS;
    }

    return 0;
}