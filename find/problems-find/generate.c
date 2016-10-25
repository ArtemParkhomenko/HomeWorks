/**
 * generate.c
 *
 * Generates pseudorandom numbers in [0,MAX), one per line.
 *
 * Usage: generate n [s]
 *
 * where n is number of pseudorandom numbers to print
 * and s is an optional seed
 */
 
#define _XOPEN_SOURCE

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// upper limit on range of integers that can be generated
#define LIMIT 65536

int main(int argc, string argv[])
{
    // TODO: если аргументов не 2 и не три вернуть ошибку
    if (argc != 2 && argc != 3)
    {
        printf("Usage: ./generate n [s]\n");
        return 1;
    }

    // TODO: преобразование второго аргумента из строки в целочисленный тип
    int n = atoi(argv[1]);

    // TODO: если аргумента три, то для генерации псевдослучайных чисел использовать аргумент 3, преобразованный в целочисленный тип;
    if (argc == 3)
    {
        srand48((long) atoi(argv[2]));
    }
    else // Если false, то для генерации чисел использовать текущую дату
    {
        srand48((long) time(NULL));
    }

    // TODO: цыкл вывода сгнерированых чисел не больше лимита.
    for (int i = 0; i < n; i++)
    {
        printf("%i\n", (int) (drand48() * LIMIT));
    }

    // success
    return 0;
}
