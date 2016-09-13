#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    int sum = 0;
    int cents25 = 0;
    int cents10 = 0;
    int cents5 = 0;
    int cents1 = 0;
  //  int index = 0;

    do                  // проверка на целое число больше ноля 
    {
        printf("You gave me number of cents: "); 
        sum = GetInt();
        if (sum == 0||sum <= 0)
        printf("retype\n:");
    }
    while(sum <= 0); 
    
    cents25 = sum % 25;
    cents10 = cents25 % 10;
    cents5 = cents10 % 5;
    cents1 = cents5 % 1;
    printf ("%d\n", cents1);
    
}
