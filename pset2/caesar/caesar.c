#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

// Prototype functions
bool only_digits(string s);
int rotate(char c, int n);

int main(int argc, string argv[])
{
    // Verifica a quantidade de argumentos e se tem apenas dígitos
    if (argc != 2 || only_digits(argv[1]) != true)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // Converte o argumento para inteiro e pede o texto para o usuário
    int key = atoi(argv[1]);
    string plaintext = get_string("plaintext: ");

    // Encipher the Plaintext
    printf("ciphertext: ");
    for (int i = 0, n = strlen(plaintext); i < n; i++)
    {
        printf("%c", rotate(plaintext[i], key));
    }
    printf("\n");
    return 0;
}

// Verifica se o argumeto da linha de comando é um dígito inteiro
bool only_digits(string s)
{
    bool digit;
    for (int i = 0, n = strlen(s); i < n; i++)
    {
        digit = isdigit(s[i]);
    }
    return digit;
}

// Transforma e depois rotaciona os caracteres entre todas as letras do alfabeto
int rotate(char c, int n)
{
    if (isupper(c))
    {
        int upper_alpha_index = c - 65;
        int formula_upper = (upper_alpha_index + n) % 26;
        return formula_upper + 65;
    }
    else if (islower(c))
    {
        int lower_alpha_index = c - 97;
        int formula_lower = (lower_alpha_index + n) % 26;
        return formula_lower + 97;
    }
    else
    {
        return c;
    }
}