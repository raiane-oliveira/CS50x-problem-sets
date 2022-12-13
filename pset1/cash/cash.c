#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Pergunta ao usuário o troco devido
    float cents;
    do
    {
        cents = get_float("Change owed: ");
    }
    while (cents <= 0);

    // Subtrai o valor de cada moeda e vai contando quantas estão sendo usadas
    int coins = 0;
    while (cents >= 25)
    {
        cents -= 25;
        coins++;
    }

    while (cents >= 10)
    {
        cents -= 10;
        coins++;
    }

    while (cents >= 5)
    {
        cents -= 5;
        coins++;
    }

    while (cents >= 1)
    {
        cents -= 1;
        coins++;
    }

    // Imprime quantas moedas foram usadas para o troco
    printf("%i coins\n", coins);
}
