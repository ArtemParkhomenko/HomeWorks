#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h> 
#include <stdlib.h>

int main(){
    int key = 0;
    do{
        printf("You gave me number K: ");
        key = GetInt();   //get key 
        if (key == 0||key <= 0){
        printf("retype: ");
        }
    }
    while(key <= 0);
    printf("k = %d\n", key);
    char myString [100];
    printf("Print text: ");
    fgets (myString, 100, stdin);
    int i = 0;
    while (myString[i]){
        printf("%c", myString[i]+key);
        i++;
    }
}
 
