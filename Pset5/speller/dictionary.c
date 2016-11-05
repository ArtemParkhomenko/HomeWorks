#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

unsigned int dictionarySize = 0;
Node *root;

/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    Node *cursor = root;
    
    for (int i = 0, l = strlen(word); i < l; i++)
    {
        int c = tolower(word[i]);
        int index = (c == '\'') ? CHARACTERS - 1 : c - 'a';
        
        if (cursor->children[index] == NULL)
        {
            return false;
        }
        
        cursor = cursor->children[index];
    }
    
    return (cursor->word) ? true : false;
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    
    FILE *fp = fopen(dictionary, "r");
    if (fp == NULL)
    {
        printf("Could not open %s.\n", dictionary);
        return false;
    }
    
    // initialize root of the trie
    root = (Node *) malloc(sizeof(Node));
    for (int i = 0; i < CHARACTERS; i++)
    {
        root->children[i] = NULL;
    }
    root->word = false;
    
    Node *cursor = root;
    
    for (int c = fgetc(fp); c != EOF; c = fgetc(fp))
    {
        if (c == '\n')
        {
            cursor->word = true;        
            cursor = root;
            dictionarySize++;
        }
        else
        {
            
            int index = (c == '\'') ? CHARACTERS - 1 : c - 'a';
            if (cursor->children[index] == NULL)
            {
                cursor->children[index] = (Node *) malloc(sizeof(Node));
                for (int i = 0; i < CHARACTERS; i++)
                {
                    cursor->children[index]->children[i] = NULL;
                }
                cursor->children[index]->word = false;
            }
            cursor = cursor->children[index];
        }
    }
    
    fclose(fp);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return dictionarySize;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    return freeNode(root);
}

/**
 * Recursivly free every Node
 */
bool freeNode(Node *Node)
{
    for (int i = 0; i < CHARACTERS; i++)
    {
        if (Node->children[i] != NULL)
        {
            freeNode(Node->children[i]);
        }
    }
    
    free(Node);
    return true;
}