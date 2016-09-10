#include <stdio.h>

#include <cs50.h>



int main(void)

{

    int namber = GetInt ();

    for (int i = 0; i < namber; i++){

        for (int m = 0; m < i; m++){

            printf ("*");

        }

        printf ("\n");

        }

}