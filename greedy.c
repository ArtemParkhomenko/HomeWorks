#include <stdio.h>
#include <cs50.h>

int main(void) 
{
    int sum = 0;  // сумма сдачи
    int cents25 = 0; // остаток от деления на 25
    int cents10 = 0;
    int cents5 = 0;
    int cents1 = 0;
    int index25 = 0; // количсество монет номинало 25
    int index10 = 0;
    int index5 = 0;
    int index1 = 0;
    do                  // проверка на целое число больше ноля 
    {
        printf("You gave me number of cents: "); 
        sum = GetInt();
        if (sum == 0||sum <= 0)
        printf("retype\n:");
    }
    while(sum <= 0); 
    cents25 = sum % 25; // количсество монет номинало 25
    index25 = (sum - cents25) / 25;
    printf ("25 cents coins: %d,\n", index25); 
    cents10 = cents25 % 10; // количсество монет номинало 10
    index10 = (cents25 - cents10) / 10;
    printf ("10 cents coins: %d,\n", index10); 
    cents5 = cents10 % 5; // количсество монет номинало 5
    index5 = (cents10 - cents5) / 5;
    printf ("5 cents coins: %d,\n", index5); 
    cents1 = cents5 % 1; // количсество монет номинало 1
    index1 = (cents5 - cents1);
    printf ("1 cents coins: %d,\n", index1); 
    printf ("coints sum: %d\n", index25 + index10 + index5 + index1); // выводит общее количество монет
}
