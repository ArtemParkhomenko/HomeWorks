#include <stdio.h>
#include <cs50.h>


void buildingPiramid (int number);  // прототипы функций
int validNumber(int number);

int main(){  
    int number = 0;
    buildingPiramid (validNumber(number));
}

int validNumber(int number){
    do{ // проверка на целое число больше ноля и не больше 23
        printf ("height: ");
        number = GetInt();
    }
    while(number < 0||number > 23); 
    return number;
}

void buildingPiramid (int number){ // построение пирамиды
    for(int i = 1; i <= number; i++){
        for(int j = 1; j <= number - i; j++){
            printf(" ");
        }
        for(int j = 1; j <= i + 1; j++){
            printf("#");
        }
        printf("\n");
    }
}

