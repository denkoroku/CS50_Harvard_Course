

// Implements a dictionary's functionality


#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5381;

// Hash table
node *table[N];
int dictionaryWords = 0;


//set node head
node *head = NULL;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int length = strlen(word);
    char lowerCase[length + 1];

    //make lowercase
    lowerCase[length] = '\0';
    for (int i = 0; i < length; i++)
    {
        lowerCase[i] = tolower(word[i]);
    }

    //hash the lowercase word
    int index = hash(lowerCase);
    node *n = table[index];

    //if no node at that index then word is not in dictionary
    if (n == NULL)
    {
        return false;
    }

    //if node exists at that index
    while (n != NULL)
    {
        if (strcasecmp(n->word, lowerCase) == 0)
        {
            return true;
        }
        //set the pointer
        n = n->next;
    }

    return false;
}

// Hash function to change word to a number
//Hash function based on  https://stackoverflow.com/questions/7700400/whats-a-good-hash-function-for-english-words

unsigned int hash(const char *word)
{
    unsigned long hash = N;

    int c = *word;

    while (c == *word++)
    {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % N;
}


// Loads dictionary into memory, returning true if successful
bool load(const char *dictionary)
{
    // open the dictionary file
    FILE *dictionary_data = fopen(dictionary, "r");

    //check if file opened ok
    if (dictionary_data == NULL)
    {
        return false;
    }

    {
        // set word variable including end character
        char word[LENGTH + 1];

        while (fscanf(dictionary_data, "%s", word) != EOF)
        {
            node *n = malloc(sizeof(node));

            //check for memory error
            if ( n == NULL )
            {
                return false;
            }

            else
            {
                strcpy(n->word,word);
                n->next = NULL;

                //hash the word to get the index
                unsigned int index = hash(word);

                //insert the node at begining of linked list
                n->next = table[index];
                table[index] = n;

                //increase the count for words in dictionary
                dictionaryWords++;
            }
        }
    fclose(dictionary_data);
    return true;
   }
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
     if (dictionaryWords > 0)
    {
        return dictionaryWords;
    }

    else
    {
       return 0;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload( void )
{
  // for each bucket in table
    for ( int i = 0; i < N ; i++ )
    {
        while(table[i] != NULL)
        {
            //create cursor so dont loose head

            node* cursor = table[i];
            table[i] = cursor->next;

            //free the cursor memory
            free(cursor);
        }
    }

    return true;
}

