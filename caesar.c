#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


void execution (int key); // прототип функции

int main(int argc, string argv[]){
    int key = atoi(argv[1]); // переменная для ключя, приведение к типу инт функцией "атои"
    if(argc != 2 && key <= 0){  //проверка количества аргументов и ключа на <= 0
        printf ("You have to enter the key is greater than zero. \n");
        return 1; // в случае не выполнения одного из условий вернуть 1 
    }
    execution(key);
    return 0;  
}

void execution (int key){
    string text = get_string();
    int length = strlen(text);
    for(int i = 0; i < length; i++){
        if(isalpha(text[i])){
            if(islower(text[i])){
                printf("%c", ((((text[i] - 'a') + key) % 26) + 'a'));
            }
            else{
                printf("%c", ((((text[i] - 'A') + key) % 26) + 'A'));
            }
        }
        else{
            printf("%c", text[i]);
        }
    }
    printf("\n");
}
