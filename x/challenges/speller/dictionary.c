// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents number of buckets in a hash table
//#define N 26
//#define N 5381
//#define N 65537
//#define N 8191
#define N 32771
//#define N 16381

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Represents a hash table
node *hashtable[N];

// Hashes word to a number between 0 and 25, inclusive, based on its first letter
unsigned int hash(const char *word)
{
//    return tolower(word[0]) - 'a';

// djb2 algorithm by Dan Bernstein
    unsigned int hash = 5381;

    int c;
    while ((c = *word++))
        hash = ((hash << 5) + hash) + tolower(c); /* hash * 33 + c */

    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Initialize hash table
    node **e = hashtable;
    for (int i = 0; i < N; i++)
        *e++ = NULL;

    // Open dictionary
    FILE *file = fopen(dictionary, "r");
    if (!file)
    {
        unload();
        return false;
    }

    // Buffer for a word
    char word[LENGTH + 1];

    // Insert words into hash table
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create a node with the word
        node *ptr;
        if (!(ptr = malloc(sizeof(node))))
        {
            unload();
            return false;
        }

        strcpy(ptr->word, word);

        // Insert the node in the corresponding list
        node **entry = hashtable + hash(word);
        ptr->next = *entry;
        *entry = ptr;
    }

    // Close dictionary
    fclose(file);

    // Indicate success
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    // Iterate over hashtable
    int n = 0;
    node **e = hashtable;
    for (int i = 0; i < N; i++)
    {
        // Count words in the list for the hashtable entry
        for(node *ptr = *e++; ptr; ptr = ptr->next)
            n++;
    }

    return n;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Check if the word is in the corresponding list
    for (node *ptr = hashtable[hash(word)]; ptr; ptr = ptr->next)
    {
        if (strcasecmp(word, ptr->word) == 0)
            return true;
    }

    return false;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // Iterate over hashtable
    node **e = hashtable;
    for (int i = 0; i < N; i++)
    {
        node *next;
        for (node *ptr = *e++; ptr; ptr = next)
        {
            next = ptr->next;
            free(ptr);
        }
    }

    return true;
}
