#include <stdio.h>
#include <cs50.h>

int main(void) 
{

    int cents = 0;

    do 
    {
        printf("You gave me number of cents: ");
        cents = GetInt();
        if (cents == 0||cents <= 0)
        printf("retype\n:");
    }
    while(cents <= 0);
    
    if (cents > 50){
        for (i = cents; i >= 0; i - 50)
    }


}
