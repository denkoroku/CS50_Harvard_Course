// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <strings.h>


// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
unsigned int N = 1;

// Make Hash table
node *table[1000];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // hash the word
    int index = hash(word);
    //access linked list at that index

    if (table[index] == NULL)
    {
        return false;
    }

    //traverse linked list looking for the word (strcasecmp) compares case insensitively
       //set cursor to first item in linked list
       node* cursor = table[index];
       //move the cursor to next item
       while (cursor != NULL)
       {
           if (strcasecmp(word, cursor->word) == 0)
           {
               return true;
           }
           cursor = cursor->next;
       }
        return false;
}

// Hashes word to a number
// Source of function: stackoverflow.com/questions/14409466/simple-hash-functions

unsigned int hash(const char *word)
{
    unsigned int count;
    unsigned int hashValue = 0;
    for(count = 0; word[count] != '\0'; count++)
        hashValue = word[count] + (hashValue << 6) + (hashValue << 16) - hashValue;

    return (hashValue % N);
}


// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // open the dictionary file
    FILE *dictionary_data = fopen(dictionary, "r");


    // Check for NULL return
    if (dictionary_data == NULL)
    {
        printf("Error: cannot open file\n");
        return 1;
    }

    char word[LENGTH+1];

        //repeat until reach EOF
            while (fscanf(dictionary_data, "%s", word) != EOF)
            {
                // allocate memory for next word
                    node* nextWord = malloc(sizeof(node));

                // create a new node
                node *n = malloc(sizeof(node));
                    if (n == NULL)
                        {
                            return 1;
                        }
                strcpy(nextWord->word, word);
                n->next = NULL;
                free(nextWord);

        //hash the word
        int index = hash(word);

        //insert node into hash table
        if (table[index] == NULL)
        {
            table[index] = n;
            n->next = NULL;
        }

        else
        {
            n->next = table[index];
            table[index] = n;
        }

        N++;
    }

    //close dictionary file
        fclose(dictionary_data);

    //return success
        return true;

}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return (N-1);
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    //create cursor and tmp variables so dont loose head
    node* cursor = table[0];
    node* tmp = table[0];

    for (int i=0; i< N; i++)
    {
        while(table[i] !=NULL)

        {
            tmp = cursor;
           cursor = cursor->next;
            free(tmp);

        }



    }

    return true;
}
