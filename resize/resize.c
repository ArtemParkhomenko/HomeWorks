/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[]) 
{
    // ensure proper usage
    if (argc != 4)                                          // Если аргументов не 4, вернуть 1; 
    {
        fprintf(stderr, "Usage: ./resize infile outfile\n");
        return 1;
    }

    // remember filenames
    int size = atoi(argv[1]);                               // Коефициент размера;
    char *infile = argv[2];                                 // Имя исходящего файла;
    char *outfile = argv[3];                                // Имя входящего файла;
        
    if (size < 1 || size > 100)                             // Проверка полученого размера.
    {
        fprintf(stderr, "Usage: size should not be less than zero.\n");
        return 1;
    }

    // open input file 
    FILE *inptr = fopen(infile, "r");                       // Создание указателя на объект типа файл, который принимается на вход;
    if (inptr == NULL)                                      // Если файла нет;
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");                     // Создание указателя на объект типа файл, который выводится;
    if (outptr == NULL)                                     // Если файла нет;
    {
        fclose(inptr);                                      // Закрыть файл;
        fprintf(stderr, "Could not create %s.\n", outfile); 
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;                                    // Считывание информации о размере и типе файла; 
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;                                    // Считывание с заголовочного файла информации о размере и цветовом формате;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    BITMAPINFOHEADER source;
    source = bi;

    bi.biWidth *= size;
    bi.biHeight *= size;
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingRes =  (4 - (source.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    bi.biSizeImage = ((sizeof(RGBTRIPLE) * bi.biWidth) + padding) * abs(bi.biHeight);
    bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);       // Запись информации о размере и типе файла в исходящий файл; 

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);       // Запись в заголовочны файла информации о размере и цветовом формате;


    // iterate over infile's scanlines
                              
    
    for (int i = 0, biHeight = abs(source.biHeight); i < biHeight; i++){
        
        long position = ftell(inptr);                     // Определение значения указателя на текущее положение в файле;
        
        for (int n = 0; n < size; n++){
            fseek(inptr, position, SEEK_SET);             // Востановление указателя;
            
            // iterate over pixels in scanline
            for (int j = 0; j < source.biWidth; j++){
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // write RGB triple to outfile
                for(int m = 0; m < size; m++){
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
    
            // skip over padding, if any
            fseek(inptr, paddingRes, SEEK_CUR);
    
            // then add it back (to demonstrate how)
            for (int k = 0; k < padding; k++){
                fputc(0x00, outptr);
            }
        }
    }

    // close infile
    fclose(inptr);                                       // Закрываем входящий файл;

    // close outfile
    fclose(outptr);                                      // Закрываем исходящий файл.
    
    // success
    return 0;
}
