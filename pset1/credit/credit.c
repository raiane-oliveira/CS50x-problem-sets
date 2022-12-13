#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // Pergunta ao usuário o seu cartão de crédito
    long card = get_long("Número do seu cartão de crédito: ");

    // Calcula quantos dígitos tem
    long credit_c = card;
    int i = 0;
    do
    {
        credit_c /= 10;
        i++;
    }
    while (credit_c > 0);

    // Imprime e verifica se os dígitos do cartão é válido
    if (i != 13 && i != 15 && i != 16)
    {
        printf("INVALID\n");
        return 0;
    }

    // Coleta os dois primeiros dígitos
    long marca = card;
    int marca_d;

    if (i == 15)
    {
        while (marca > 0)
        {
            marca_d = marca % 1000;
            marca /= 1000;
        }
    }
    else if (i == 13 || i == 16)
    {
        while (marca > 0)
        {
            marca_d = marca % 100;
            marca /= 100;
        }
    }

    // Calcular o checksum
    int d2, d1, multi_d2, sum_d1 = 0, sum_d2 = 0, total;
    while (card > 0)
    {
        // Armazena o último digito, divide o cartão e soma
        d1 = card % 10;
        card /= 10;

        // Armazena o penultimo digito, divide o cartão e multiplica por dois
        d2 = card % 10;
        card /= 10;

        // Multiplica, separa cada unidade e soma
        multi_d2 = d2 * 2;
        multi_d2 = multi_d2 / 10 + multi_d2 % 10;
        sum_d1 += d1;
        sum_d2 += multi_d2;
    }
    total = sum_d1 + sum_d2;

    // Verifica se a marca do cartão é verdadeira
    if (total % 10 == 0)
    {
        if (marca_d / 10 == 34 || marca_d / 10 == 37)
        {
            printf("AMEX\n");
        }
        else if (marca_d / 10 == 5 && marca_d % 10 > 0 && marca_d % 10 < 6)
        {
            printf("MASTERCARD\n");
        }
        else if (marca_d % 10 == 4 || marca_d / 10 == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}