#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void encryption (int key); // прототип функции

int main(int argc, string argv[]){
    
    if (argc < 2 || argc > 2){  //проверка количества аргументов
        printf ("print argument two \n");
        return 1; // в случае не выполнения одного из условий вернуть 1 
    }
    
    int key = atoi(argv[1]); // переменная для ключя, приведение к типу инт функцией "атои"
    
    if (key <= 0){ // проверка ключа на положительное число
        printf ("print key > 0 \n");
        return 1; // в случае не выполнения условия вернуть 1 
    }
    
    encryption (key); // вызов функции шифрования
    
    return 0;  
}

void encryption (int key){
    
    printf ("plaintext: "); // приглашение на ввод
    string plaintext = get_string(); // принимаем строку
    int lengthString = strlen (plaintext); // определяем длинну строки
    printf ("ciphertext: "); //вывод шифрованого текста
    
    for (int i = 0; i < lengthString; i++){ // цыкл шифрования
        if (isalpha (plaintext[i])){ // проверк на наличие символа в алфавите
            if (islower (plaintext[i])){ // проверка прописных и строчных символов
                printf ("%c", ((((plaintext[i] - 'a') + key) % 26) + 'a')); // шифрование маленьких букв
            }
            else {
                printf ("%c", ((((plaintext[i] - 'A') + key) % 26) + 'A')); //шифрование больших букв
            }
        }
        else {
            printf ("%c", plaintext[i]); 
        }
    }
    
    printf ("\n");
}
