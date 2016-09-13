#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    int sum = 0;
    int cents25 = 0;
    int cents10 = 0;
    int cents5 = 0;
    int cents1 = 0;
    int index = 0;
    int index10 = 0; 

    do                  // проверка на целое число больше ноля 
    {
        printf("You gave me number of cents: "); 
        sum = GetInt();
        if (sum == 0||sum <= 0)
        printf("retype\n:");
    }
    while(sum <= 0); 
    
    cents25 = sum % 25;
    index = (sum - cents25) / 25;
    printf ("25 cents coins: %d,\n", index);
    
    cents10 = cents25 % 10;
    index10 = (cents25 - cents10) / 10;
    printf ("10 cents coins: %d,\n", index10);
    
    cents5 = cents10 % 5;
    index = (cents10 - cents5) / 5;
    printf ("5 cents coins: %d,\n", index);
    
    cents1 = cents5 % 1;
    index = (cents5 - cents1);
    printf ("1 cents coins: %d,\n", index);
}
