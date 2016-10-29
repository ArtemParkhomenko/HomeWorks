#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define SIZE 512                                 
typedef uint8_t BYTE;                           
bool isJPEG(BYTE* p);                           

int main(void)
{
    FILE* file = fopen("./card.raw", "r");
    FILE* temp;
    BYTE* buf = malloc(SIZE);
    char* filename = malloc(sizeof(char) * 8);
    int count = 0;
    bool fileOpened = false;
    if (file == NULL){
        fprintf(stderr,"Could't open card.raw\n");
        return 1;
    }
    if (buf == NULL){
        printf("Error memory\n");
        return 2;
    }
    
    while(fread(buf, sizeof(buf), 1, file) == 1){   
        if(isJPEG(buf)){
            sprintf(filename, "%03d.jpg", count);
            count++;
            
            if(fileOpened){
                fclose(temp);
                temp = fopen(filename, "w");
                fwrite(buf, sizeof(buf), 1, temp);
            }
            else{
                temp = fopen(filename, "w");
                fwrite(buf, sizeof(buf), 1, temp);
                fileOpened = true;
            }             
        }     
        else if (fileOpened)
        {
            fwrite(buf, sizeof(buf), 1, temp);
        }
    }
    
    fclose(temp);                               
    fclose(file);                              
     
    free(filename);                            
    free(buf);                                  

    return 0;
}

bool isJPEG(BYTE* p){
    return (p[0] == 0xff && p[1] == 0xd8 && p[2] == 0xff && (p[3] == 0xe0 || p[3] == 0xe1));
}