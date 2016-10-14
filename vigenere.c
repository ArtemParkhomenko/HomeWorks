#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

void execution(string durationKey);      // Прототип функции; 
char ciphertext(char sign, int key);     

int main(int argc, string argv[]){       // Пердаем параметр - строку;
    string durationKey = "";             // Обнуление строковой переменной; 
    if(argc == 2){                       // если введено два аргумента; 
        int length = strlen(argv[1]);    // Длинна ключа
        for(int i = 0; i < length; i++){ // Выполнять цыкл пока и меньше длинны ключа;
            if(!isalpha(argv[1][i])){    // Проверка ключа на строчные и заглавные буквы;
                printf("warning. \n");   // Вывести ошибку если isalpha вернет fals;
                return 1;                // Вернуть 1, ошибка;
            }
            else{                        // если ключь удовлетворяет условие записать его в переменную;
                durationKey = argv[1];
            }
        }
    }
    else{                                // Если аргуметов не 2, то вывести ошибку
        printf("enter key \n");  
        return 1;
    }
    execution(durationKey);              // Вызов функции 
    return 0;  
}

void execution(string durationKey){
    int keyYardage = strlen(durationKey); // Определение длинны слова-ключа;
    int keyNumbers[keyYardage];           // Создание масива зармера длинны слова-ключа;
    
    int keyScoring = 0;                    // переменная счетчик

    for(int i = 0; i < keyYardage;i++){
        keyNumbers[i] = toupper(durationKey[i]) - 'A'; // получение чисельных значений симловол в таблице аскии
    }
    printf("plaintext: ");               // введите текст
    string text = GetString();           // запись строки в строковую переменную
    int textLength = strlen(text);       // определение длинны введенной строки
    printf("ciphertext: "); 
    for (int i = 0; i < textLength; i++){// цыкл вывод зашифрованого текста
        if(!isalpha(text[i])){           // если елемент строки не символ то выводим его без изменений 
            printf("%c", text[i]); 
        }
        else{                            // если символ 
            printf("%c", ciphertext(text[i], keyNumbers[keyScoring]));  // вывод текста 
            if(keyScoring < keyYardage - 1){                            // если счеткчик меньше длинны строки - 1, счетчик ++ 
                keyScoring++;
            }   
            else{                                                       // иначе сбросить счетчик на 0
                keyScoring = 0;
            }
        }
    }
    printf("\n");
}

char ciphertext(char sign, int key){                //caesar algoritm
    if(islower(sign)){
        return ((((sign - 'a') + key) % 26) + 'a'); // если строчная буква
    }
    else{
        return ((((sign - 'A') + key) % 26) + 'A'); // если большая буква
    }
}