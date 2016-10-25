/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n == 0){
        return false;
    }
    else if(values[0]>value){
        return false;
    }
    else if(values[n - 1]<value){
        return false;
    }
    
    int start = 0;
    int end = n;
    
    while(start<end){
        int middle = start + (end - start) / 2;
        if(value <= values[middle]){
            end = middle;
        }
        else{
            start = middle + 1;
        }
    }
    if (values[end] == value){
        return true;
    }
    else{
        return false;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
for(int i = 0; i < n - 1; i++){
        int tempIndex = i;
        for(int j = i + 1; j < n; j++){
            if(values[j] < values[tempIndex]){
                tempIndex = j;
            }
        }
        int temp = values[i];
        values[i] = values[tempIndex];
        values[tempIndex] = temp;
    }
    return;
}


