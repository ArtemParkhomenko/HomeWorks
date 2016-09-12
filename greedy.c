#include <stdio.h>
#include <cs50.h>

int main(void) 
{

    int cents = 0;      //Необходимая сдача
    int index = 0;      //количствво монет в остаче
    int i = 0;

    do                  // проверка целое ли число 
    {
        printf("You gave me number of cents: "); 
        cents = GetInt();
        if (cents == 0||cents <= 0)
        printf("retype\n:");
    }
    while(cents <= 0); 
    
    if (cents > 50){   //Количество по монет номиналом 50
        for (i = 0; cents < 49; i++){
        cents = cents - 50;
        index = index + i;
        }
    }
            else if (cents < 50){   //Количество по монет номиналом 25
                for (i = 0; cents < 24; i++){
                cents = cents - 25;
                index = index + i;
                }
            }
                else if (cents < 25){   //Количество по монет номиналом 10
                    for (i = 0; cents < 9; i++){
                    cents = cents - 10;
                    index = index + i;
                    }
                }
                    else if (cents < 10){   //Количество по монет номиналом 5
                        for (i = 0; cents < 4; i++){
                        cents = cents - 5;
                        index = index + i;
                        }
                    }
                            else if (cents < 5){   //Количество по монет номиналом 1
                                for (i = 0; cents == 0; i++){
                                cents = cents - 1;
                                index = index + i;
                                }
                            }
    printf ("%d\n", index);
}
