#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void){
    float coints = 0;
    int index = 0;
    int rest = 0;
    do{   // запрос суммы сдачи, и проверка на больше ноля
        printf("How much money? \n"); 
        coints = GetFloat(); 
    }  
    while (coints <= 0);
    rest = round(coints * 100); // округление до ближайшего целого числа
    index = (rest / 25); //монеты по 25
    index = round(index);
    rest = rest % 25; // остаток целый остаток от деления на 25
    index = index + (rest / 10);  //монеты по 10
    index = round(index);
    rest = rest % 10;
    index = index + (rest / 5); //монеты по 5
    index = round(index);
    rest = rest % 5;
    printf("%d\n", index + rest); // выводит общее количество монет
}
