#include <stdio.h>
#include <cs50.h>

int main(void){
    int namber = GetInt ();
    for (int i = 0; i < namber; i++){
        for (int m = 0; m < namber-i-1; m++){
            printf ("%s", " ");
        }
        for(int a = 0; a < i+1; a++){
            printf("*");
        }
        printf ("\n");
    } 
}
