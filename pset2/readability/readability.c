#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // Pega o texto do usuário
    string text = get_string("Text: ");

    // Calcula a quantidade de letras, palavras e sentenças
    int L = 0;
    int words = 0;
    int S = 0;
    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (islower(text[i]) || isupper(text[i]))
        {
            L++;
        }
        else if (isspace(text[i]))
        {
            words++;
        }
        else if (text[i] == '!' || text[i] == '.' || text [i] == '?')
        {
            S++;
        }
    }
    words += 1;

    //Coleman-Liau Formula
    double index = 0.0588 * L / words * 100 - 0.296 * S / words * 100 - 15.8;
    int grade = (int) round(index);

    // Condição para saber o nível de escolaridade
    if (grade <= 0)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}