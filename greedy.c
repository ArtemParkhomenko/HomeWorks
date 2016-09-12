#include <stdio.h>
#include <cs50.h>

int main(void) 
{

    int cents = 0;      //Необходимая сдача
    int quantity = 0;   //количество монет
    int balance = 0;    //остача
    int index = 0;      //количствво монет в остаче

    do                  // проверка целое ли число 
    {
        printf("You gave me number of cents: "); 
        cents = GetInt();
        if (cents == 0||cents <= 0)
        printf("retype\n:");
    }
    while(cents <= 0); 
    if (cents > 50){    //Количество по монет номиналом 50
    for (index = 0; cents == 0; i++){
        balance = cents - 50;
        quantity = index + i;
        }
    }
    else if(balance > 25)  //Количество по монет номиналом 25
    for ( = 0; cents == 0; i++){
        balance = cents - 25;
        quantity = i;
    }
}
