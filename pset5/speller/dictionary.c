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
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 5000;

// Hash table
node *table[N];

// Words counter
unsigned int words = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // Calculate hash value
    unsigned int h = hash(word);

    // Search the hash table at specified location
    for (node *ptr = table[h]; ptr != NULL; ptr = ptr->next)
    {
        if (strcasecmp(ptr->word, word) == 0)
        {
            return true;
        }
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    unsigned int hash = 0;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        int value = isalpha(word[i]) ? toupper(word[i]) - 'A' : 26;
        hash += value * i;
    }

    return hash % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Set all pointers in the hash table to NULL
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    // Open the dictionary file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        return false;
    }

    // Read each word in the file
    char word[LENGTH + 1];

    while (fscanf(file, "%s", word) != EOF)
    {
        // Calculate hash value
        unsigned int h = hash(word);

        // Create new hash table node
        node *word_node = malloc(sizeof(node));
        if (word_node == NULL)
        {
            unload();
            return false;
        }

        strcpy(word_node->word, word);
        word_node->next = table[h];
        table[h] = word_node;

        // Update counter
        words++;
    }

    // Close the dictionary file
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return words;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // Iterate through the hash table
    for (int i = 0; i < N; i++)
    {
        // Free the memory at specified location
        node *ptr = table[i];
        while (ptr != NULL)
        {
            node *next = ptr->next;
            free(ptr);
            ptr = next;
        }
    }

    return true;
}
