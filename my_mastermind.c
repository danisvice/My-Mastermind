#include <stdio.h>
#include <stdlib.h>

#define CIFRE 4

int main()
{
    int num_ok, pos_no_ok;
    int i;
    int tentativo;
    int num_tentativi = 0;

    int codice[CIFRE] = {};
    int tentativo_utente[CIFRE] = { 0 };
    int usata[CIFRE] = { 0 };
    int usata_s[CIFRE] = { 0 };


    for (i = 0; i < CIFRE; i++)
    {
        codice[i] = rand() % (9) + 1;
        printf("%d", codice[i]);
    }

    printf("\n");

    //initialize the arrays here so the attempt count is correct,
    //otherwise the count will start from 1 onwards if they were initialized at the beggining of the code.
    //each attempt will restart at 0 out of 10 attempts available.
    do
    {
        num_ok = 0;
        pos_no_ok = 0;

        for(int i = 0; i < CIFRE; i++)
        {
            usata[i] = 0;
            usata_s[i] = 0;
        }
    }
    while(num_tentativi != 10);

    printf("Will you find the secret code? Please enter a valid guess");
    scanf("%d", &tentativo);

    return 0;
}