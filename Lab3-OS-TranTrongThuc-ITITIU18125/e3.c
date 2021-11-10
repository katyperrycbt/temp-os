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

struct book
{
    char *title;
    int price;
};

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

    if (!checkNumber(args->num) || atoi(args->num) < 0 || atoi(args->num) > 10)
    {
        printf("???????????????????\n'%s' is not a VALID number (0<n<10), this argument has been skipped\n???????????????????\n", args->num);
    }
    else
    {
        struct book book1, book2, book3, book4, book5, book6, book7, book8, book9, book10;

        book1.title = "Things Fall Apart";
        book1.price = 35547;

        book2.title = "Fairy tales";
        book2.price = 27000;

        book3.title = "The Divine Comedy";
        book3.price = 15475;

        book4.title = "The Epic Of Gilgamesh";
        book4.price = 76452;

        book5.title = "The Book Of Job";
        book5.price = 97542;

        book6.title = "One Thousand and One Nights";
        book6.price = 54721;

        book7.title = "Pride and Prejudice";
        book7.price = 42412;

        book8.title = "Molloy, Malone Dies, The Unnamable, the trilogy";
        book8.price = 22425;

        book9.title = "The Decameron";
        book9.price = 85725;

        book10.title = "Ficciones";
        book10.price = 65472;

        printf("-------------------------------------\n");
        printf("Thread %ld\n", args->thread_id);
        int sum = 0;
        for (int i = 0; i < atoi(args->num); i++)
        {
            int randomIdx = rand() % 11;
            struct book selectedBook;
            switch (randomIdx)
            {
            case 1:
                selectedBook = book1;
                break;
            case 2:
                selectedBook = book2;
                break;
            case 3:
                selectedBook = book3;
                break;
            case 4:
                selectedBook = book4;
                break;
            case 5:
                selectedBook = book5;
                break;
            case 6:
                selectedBook = book6;
                break;
            case 7:
                selectedBook = book7;
                break;
            case 8:
                selectedBook = book8;
                break;
            case 9:
                selectedBook = book9;
                break;
            case 10:
                selectedBook = book10;
                break;
            default:
                selectedBook = book1;
            }
            printf("%s\n", selectedBook.title);
            sum = sum + (int)selectedBook.price;
        }
        printf("Total Price: %d\n", sum);
        printf("-------------------------------------\n");
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
