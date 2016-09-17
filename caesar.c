#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h> 
#include <stdlib.h>


int main(){
    printf("You gave me number K: "); 
    int key = 0; GetInt();   //get key 
    return key;
} 
int getk(key){
    do{
        key = GetInt();
        if (key == 0||key <= 0)
        printf("retype: ");
    }
    while(key <= 0);
    printf("k = %d\n", key);
    return key;
}
int getplaintext(key){  //get plaintex, encipher, printciphertext.
    char myString [100];
    printf("Print text: ");
    fgets (myString, 100, stdin);
    int i = 0;
    while (myString[i]){
        printf("%c", myString[i]+key);
        i++;
    }
}  
     
 