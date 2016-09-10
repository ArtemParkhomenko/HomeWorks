#include <stdio.h>

#include <cs50.h>



int main(void)

{
    
	int quantity = 0;
   
	do{

        printf ("print quantity minutes: ");

        quantity = GetInt ();

        }
    
    while (quantity < 1);

        int amount = (quantity * 12);

        printf ("sum bottles: %d\n", amount);

}