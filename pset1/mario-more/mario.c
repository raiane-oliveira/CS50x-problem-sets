#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Perguntar ao usuário e verificar a altura positiva e em um intervalo de 1 à 8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Imprime as colunas do #
    for (int i = 0; i < height; i++)
    {
        // Coloca a 1° pirâmide na direita
        for (int j = 0; j + 1 < height - i; j++)
        {
            printf(" ");
        }

        // Imprime os # da 1° pirâmide
        for (int k = 0; k < 1 + i; k++)
        {
            printf("#");
        }

        printf("  ");

        // Imprime os # da 2° pirâmide
        for (int k = 0; k < 1 + i; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}