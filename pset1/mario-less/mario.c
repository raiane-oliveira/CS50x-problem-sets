#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Verificar se a altura é positiva e no intervalo de 1 à 8
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    // Imprimir as linhas de cada #
    for (int i = 0; i < height; i++)
    {
        // Joga a pirâmide pra o lado direito
        for (int j = 0; j + 1 < height - i; j++)
        {
            printf(" ");
        }

        // Imprime os # em cada linha
        for (int k = 0; k < 1 + i; k++)
        {
            printf("#");
        }

        printf("\n");
    }
}