#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Prototype functions
bool only_alphabetical(string s);
int substitution(int index, string s, string key);

int main(int argc, string argv[])
{
    // Print an error message if the user entered an invalid jey
    if (argc != 2 || only_alphabetical(argv[1]) != 0)
    {
        printf("Usage: ./substitution A VALID KEY\n");
        return 1;
    }

    // Prompt Plaintext to the user
    string plaintext = get_string("plaintext: ");

    // Encipher
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        printf("%c", substitution(i, plaintext, argv[1]));
    }
    printf("\n");
    return 0;
}

bool only_alphabetical(string s)
{
    int key_valid = 0;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        // Check if it has 26 characters
        if (n != 26)
            return key_valid = 1;
        // Check if it's a alphabetic character
        else if (isdigit(s[i]))
            return key_valid = 1;
    }
    return key_valid;
}

int substitution(int index, string s, string key)
{
    int encipher = 0;
    // Replace plaintext for key
    if (isupper(s[index]))
    {
        return encipher = toupper(key[s[index] - 'A']);
    }
    // Lowercase
    else if (islower(s[index]))
    {
        return encipher = tolower(key[s[index] - 'a']);
    }
    else
    {
        return s[index];
    }
    return encipher;
}