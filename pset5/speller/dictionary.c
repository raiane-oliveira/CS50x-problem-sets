// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Choose number of buckets in hash table
const unsigned int N = 26;

// Keeps track of added dictionary words
int TOTAL_WORDS = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Start cursor at first item in linked list until null
    node *cursor = table[hash(word)];
    while (cursor != NULL)
    {
        // Compares two strings case-insensitively
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    return toupper(word[0]) - 'A';
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Open dictionary file
    FILE *inptr = fopen(dictionary, "r");
    if (inptr == NULL)
    {
        return false;
    }

    // Read words from dictionary
    char str[LENGTH + 1];
    while (fscanf(inptr, "%s", str) != EOF)
    {
        // Create a new node
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }
        strcpy(n->word, str);
        TOTAL_WORDS++;

        // Hash word index
        int hash_index = hash(str);

        // Insert node if firt word
        if (table[hash_index] == NULL)
        {
            n->next = NULL;
            table[hash_index] = n;
        }

        // Insert node if another word
        else
        {
            n->next = table[hash_index];
            table[hash_index] = n;
        }
    }

    // Close the dictionary
    fclose(inptr);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    if (TOTAL_WORDS == 0)
    {
        return 0;
    }
    return TOTAL_WORDS;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *tmp = table[i]->next;
            free(table[i]);
            table[i] = tmp;
        }
    }
    return true;
}